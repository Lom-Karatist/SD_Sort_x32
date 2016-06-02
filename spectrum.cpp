#include "spectrum.h"

Spectrum::Spectrum()
{
    s_owner = new QString ("");
    s_type = new QString ("");
    s_class = new QString ("");
    s_subclass = new QString ("");
    s_name = new QString ("");

}

void Spectrum::set_sOwner(QString& str){
    s_owner->append(str);
}

void Spectrum::set_sType(QString& str){
    s_type ->append(str);
}

void Spectrum::set_sClass(QString& str){
    s_class->append(str);
}

void Spectrum::set_sSubclass(QString& str){
    s_subclass ->append(str);
}

void Spectrum::set_sName(QString& str){
    s_name ->append(str);
}

QString* Spectrum::get_sOwner(){
    return s_owner;
}

QString* Spectrum::get_sType(){
    return s_type;
}

QString* Spectrum::get_sClass(){
    return s_class;
}

QString* Spectrum::get_sSubclass(){
    return s_subclass;
}

QString* Spectrum::get_sName(){
    return s_name;
}
