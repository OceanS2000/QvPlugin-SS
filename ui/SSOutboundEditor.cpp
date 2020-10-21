#include "SSOutboundEditor.hpp"
#include <QFileDialog>

SSOutboundEditor::SSOutboundEditor(QWidget *parent) : Qv2rayPlugin::QvPluginEditor(parent)
{
    setupUi(this);
}

SSOutboundEditor::~SSOutboundEditor()
{
}

QPair<QString, int> SSOutboundEditor::GetHostAddress() const
{
    return { shadowsocks.address, shadowsocks.port };
}
void SSOutboundEditor::SetHostAddress(const QString &address, int port)
{
    shadowsocks.address = address;
    shadowsocks.port = port;
}

void SSOutboundEditor::SetContent(const QJsonObject &content)
{
    shadowsocks.loadJson(content);
    //
    ssPasswordTxt->setText(shadowsocks.password);
    ssMethodCombo->setCurrentText(shadowsocks.method);
    //
    ssKeyTxt->setText(shadowsocks.key);
    ssPluginTxt->setText(shadowsocks.plugin);
    ssPluginOptTxt->setText(shadowsocks.plugin_options);
}

const QJsonObject SSOutboundEditor::GetContent() const
{
    return shadowsocks.toJson();
}

void SSOutboundEditor::on_ssKeyTxt_textEdited(const QString &arg1)
{
    shadowsocks.key = arg1;
}

void SSOutboundEditor::on_ssPasswordTxt_textEdited(const QString &arg1)
{
    shadowsocks.password = arg1;
}

void SSOutboundEditor::on_ssMethodCombo_currentTextChanged(const QString &arg1)
{
    shadowsocks.method = arg1;
}

void SSOutboundEditor::on_ssPluginTxt_textEdited(const QString &arg1)
{
    shadowsocks.plugin = arg1;
}

void SSOutboundEditor::on_ssPluginOptTxt_textEdited(const QString &arg1)
{
    shadowsocks.plugin_options = arg1;
}

void SSOutboundEditor::on_selectFilePushButton_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,tr("Plugin Executable File"),{}
                                             #ifdef Q_OS_WIN
                                                 ,tr("EXE (*.exe)")
                                             #endif
                                                 );
    if(!filename.isEmpty())
    {
        shadowsocks.plugin = filename;
        ssPluginTxt->setText(shadowsocks.plugin);
    }
}
