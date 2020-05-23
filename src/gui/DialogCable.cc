#include "DialogCable.hh"
#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <Cable.hh>
#include "QDebug"

DialogCable::DialogCable(QWidget *parent,int _type, int _debit, int _mtu,Cable * _cable)
{
    cableMemebre=_cable;
    createInputs(_type, _debit, _mtu);
    init();
    createSignals();
    update();
}


void DialogCable::createInputs(int _type, int _debit, int _mtu)
{

    mtu	 = new QLineEdit (QString::number(_mtu));
    debit= new QLineEdit (QString::number(_debit));
    appliquer=new QPushButton("Appliquer");
    type = new QComboBox();

    type->insertItem(type->count(),"Droit");
    type->insertItem(type->count(),"Croise");

    if(_type == 1){
           type->setCurrentIndex(1);
    }else{
           type->setCurrentIndex(0);
    }
}

DialogCable::~DialogCable()
{}

void DialogCable::init()
{

    QGroupBox *generalGroupBox = new QGroupBox(tr("Form Cable"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Type:")), type);
    layout->addRow(new QLabel(tr("Debit:")), debit);
    layout->addRow(new QLabel(tr("MTU:")), mtu);
    layout->addRow(appliquer);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttonBox);
    generalGroupBox->setLayout(layout);
    setLayout(layout);
    setWindowTitle(tr("Configuration de Cable"));

}

void DialogCable::createSignals()
{
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this,SIGNAL(finished(int)),this,SLOT(onExitDialog(int)));
    connect(appliquer,SIGNAL(clicked()),this,SLOT(onApplique()));

}

void DialogCable::showConfig(Cable *src)
{
    debit->setText(QString::number(src->getDebitMax()));
    mtu->setText(QString::number(src->getMTU()));

    if(src->getType() == 1)
        type->setCurrentIndex(1);
    else
        type->setCurrentIndex(0);
}

void DialogCable::onExitDialog(int)
{
    type->setCurrentIndex(0);
    mtu->setText("");
    debit->setText("");
}
void DialogCable::onApplique()
{
  int typeCable=type->currentIndex();
  cableT typeC=static_cast<cableT>(typeCable);
  cableMemebre->setType(typeC);
  cableMemebre->estBienConnecte();
  QString mtuDialog=mtu->text();
  QString debitDialog=debit->text();
  cableMemebre->setDebitMax(debitDialog.toInt());
  cableMemebre->setMTU(mtuDialog.toInt());
  showConfig(cableMemebre);

}
