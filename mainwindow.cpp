#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AES.h"
#include "Kalyna.h"
#include "DES.h"
#include "Blowfish.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBoxAlgo->insertItems(0, QStringList({"AES", "Kalyna", "DES", "Blowfish"}));
    ui->text_output_result->setReadOnly(true);

    connect(ui->encrypt_button, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(ui->decrypt_button, SIGNAL(clicked()), this, SLOT(decrypt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString DES_event(QString message, QString key, bool encrypting)
{
    bool ok;
    int n = key.toInt(&ok, 10);
    if(!ok)
    {
        n = 0;
        for(int i = 0; i < key.size(); ++i)
        {
            n += key[i].unicode();
        }
    }
    DES::keygen(n);

    QString res;
    while(message.size() % 4 != 0)
    {
        message.push_back(' ');
    }
    //std::cout << message.toStdString() << '\n';
    for(int i = 0; i < message.size(); i += 4)
    {
        long long next_chars = 0;
        for(int j = 0; j < 4; ++j)
        {
            next_chars = (next_chars << 16) + message[i + j].unicode();
        }
        if(encrypting)
        {
            next_chars = DES::encrypt(next_chars);
        }
        else
        {
            next_chars = DES::decrypt(next_chars);
        }
        for(int j = 0; j < 4; ++j)
        {
            res.push_back(QChar((unsigned short)(next_chars >> 48)));
            next_chars <<= 16;
        }
    }

    return res;
}

QString Blowfish_event(QString message, QString key, bool encrypting)
{
    char* k = key.toLocal8Bit().data();
    int k_size = key.size();


    //Blowfish::set_key_blowfish(k, k_size);


    QString res;

    while(message.size() % 4 != 0)
    {
        message.push_back(' ');
    }

    int text_size = message.size() / 2;
    uint text[text_size];


    for(int i = 0; i < message.size(); i += 2)
    {
        uint next_chars = (message[i].unicode() << 16) | message[i+1].unicode();

        text[i/2] = next_chars;

    }

    if(encrypting)
    {
        Blowfish::cipher_blowfish(text, text_size);
    }
    else
    {
        Blowfish::inv_cipher_blowfish(text, text_size);
    }

    for(int i = 0; i < text_size; ++i)
    {
        uint next_chars = text[i];
        for(int j = 0; j < 2; ++j)
        {
            res.push_back(QChar((unsigned short)(next_chars >> 16)));
            next_chars <<= 16;
        }
    }


    return res;
}


QString AES_event(QString message, QString key, bool encrypting)
{
    //message = "<²ëðQiHc·ÅZ";
    while(message.size() % 16 != 0)
    {
        message.push_back(' ');
    }

    if(key.size() > 16)
    {
        key = key.chopped(16);
    }

    while(key.size() < 16)
    {
        key.push_back('#');
    }
    int key_size = key.size();
    //QByteArray key_ba = key.toLocal8Bit();
    //uint8_t* key_arr = (uint8_t*)key_ba.data();
    std::string key_str = key.toStdString();
    uint8_t* key_arr = (uint8_t*)(key_str.c_str());

    int w_size = 44;
    uint32_t w[w_size];
    aes::key_expansion_aes(key_arr, key_size, w, w_size);

    //QByteArray message_ba = message.toLocal8Bit();
    //uint8_t* message_arr = (uint8_t*)message_ba.data();

    //uint8_t* message_arr = new uint8_t[message.size()];
    //std::copy(message.toLocal8Bit().data(), message.toLocal8Bit().data()+16, message_arr);

    std::string message_str = message.toStdString();
    uint8_t* message_arr = (uint8_t*)message_str.c_str();

    uint8_t res_arr[16];
    uint8_t res1_arr[16];
    uint8_t res2_arr[16];
    if(encrypting)
    {
        aes::cipher_aes(message_arr, res_arr, w, w_size);
        std::copy(res_arr, res_arr+16, res1_arr);
        aes::inv_cipher_aes(res1_arr, res2_arr, w, w_size);
    }
    else
    {
        aes::inv_cipher_aes(message_arr, res_arr, w, w_size);
        aes::cipher_aes(res_arr, res2_arr, w, w_size);
    }

    QString res;
    for(int i = 0; (uint)i < 16; ++i)
    {
        res.push_back(QChar(res_arr[i]));
    }
    return res;
}

QString Kalyna_event(QString message, QString key, bool encrypting)
{
    while(encrypting && message.size() % 16 != 0)
    {
        message.push_back(' ');
    }

    if(key.size() > 16)
    {
        key = key.chopped(16);
    }

    while(key.size() < 16)
    {
        key.push_back('#');
    }
    //int key_size = key.size();
    //uint8_t * key_arr = new uint8_t[16];
    //std::copy(key.toLocal8Bit().data(), key.toLocal8Bit().data()+16, key_arr);

    QByteArray key_ba = key.toLocal8Bit();
    uint8_t* key_arr = (uint8_t*)key_ba.data();

    int kalyna_nr = 10, kalyna_nb = 2;
    //uint64_t w[kalyna_nr + 1][kalyna_nb];
    uint64_t** w = new uint64_t*[kalyna_nr + 1];
    for(int i = 0; i < kalyna_nr + 1; ++i)
    {
        w[i] = new uint64_t[kalyna_nb];
    }

    kalyna::key_expansion_kalyna(key_arr, w);

    //uint8_t* message_arr = (uint8_t*)message.toLocal8Bit().data();
    //uint8_t* message_arr = new uint8_t[message.size()];
    //std::copy(message.toLocal8Bit().data(), message.toLocal8Bit().data()+16, message_arr);

    QByteArray message_ba = message.toLocal8Bit();
    uint8_t* message_arr = (uint8_t*)message_ba.data();


    uint8_t res_arr[16];
    if(encrypting)
    {
        //kalyna::cipher_kalyna(message_arr, res_arr, w);
    }
    else
    {
        //kalyna::inv_cipher_kalyna(message_arr, res_arr, w);
    }

    QString res;
    for(int i = 0; (uint)i < 16; ++i)
    {
        res.push_back(QChar((char)message_arr[i]));
    }

    for(int i = 0; i < kalyna_nr + 1; ++i)
    {
        delete [] w[i];
    }
    delete [] w;

    return res;
}

void MainWindow::encrypt()
{
    QString algo_name = ui->comboBoxAlgo->currentText();

    if(algo_name == "DES")
    {
        ui->text_output_result->setText(DES_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), true));
    }
    else if(algo_name == "Blowfish")
    {
        ui->text_output_result->setText(Blowfish_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), true));
    }
    else if(algo_name == "AES")
    {
        ui->text_output_result->setText(AES_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), true));
    }
    else if(algo_name == "Kalyna")
    {
        ui->text_output_result->setText(Kalyna_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), true));
    }
    else
    {
        ui->text_output_result->setText("enrypted" + algo_name);
    }



}

void MainWindow::decrypt()
{
    QString algo_name = ui->comboBoxAlgo->currentText();
    if(algo_name == "DES")
    {
        ui->text_output_result->setText(DES_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), false));
    }
    else if(algo_name == "Blowfish")
    {
        ui->text_output_result->setText(Blowfish_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), false));
    }
    else if(algo_name == "AES")
    {
        ui->text_output_result->setText(AES_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), false));
    }
    else if(algo_name == "Kalyna")
    {
        ui->text_output_result->setText(Kalyna_event(ui->text_input_message->toPlainText(), ui->text_input_key->toPlainText(), false));
    }
    else
    {
        ui->text_output_result->setText("decrypted" + algo_name);
    }
}
