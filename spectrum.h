#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QWidget>

class Spectrum
{
public:
    Spectrum();

    void set_sOwner(QString&);
    void set_sType(QString&);
    void set_sClass(QString&);
    void set_sSubclass(QString&);
    void set_sName(QString&);
    QString* get_sOwner();
    QString* get_sType();
    QString* get_sClass();
    QString* get_sSubclass();
    QString* get_sName();

private:
    QString* s_owner;
    QString* s_type;
    QString* s_class;
    QString* s_subclass;
    QString* s_name;
};

#endif // SPECTRUM_H
