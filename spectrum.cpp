#include "spectrum.h"

Spectrum::Spectrum()
{
    s_owner = "";
    s_type = "";
    s_class = "";
    s_subclass = "";
    s_name = "";

}
Spectrum::~Spectrum(){

}
void Spectrum::set_sOwner(QString& str){
    s_owner.append(str);
}

void Spectrum::set_sType(QString& str){
    s_type.append(str);
}

void Spectrum::set_sClass(QString& str){
    s_class.append(str);
}

void Spectrum::set_sSubclass(QString& str){
    s_subclass.append(str);
}

void Spectrum::set_sName(QString& str){
    s_name.append(str);
}

QString Spectrum::get_sOwner() const {
    return s_owner;
}

QString Spectrum::get_sType() const {
    return s_type;
}

QString Spectrum::get_sClass() const {
    return s_class;
}

QString Spectrum::get_sSubclass() const {
    return s_subclass;
}

QString Spectrum::get_sName() const {
    return s_name;
}
QString Spectrum::getParamAtIt(int It) const{

    QString str = "";

    if (It == 0){
        str = get_sOwner();
    }
    if (It == 1){
        str = get_sType();
    }
    if (It == 2){
        str = get_sClass();
    }
    if (It == 3){
        str = get_sSubclass();
    }
    if (It == 4){
        str = get_sName();
    }

    return str;
}
