#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QWidget>

class Spectrum
{
public:
    Spectrum();
    ~Spectrum();

    void set_sOwner(QString&);
    void set_sType(QString&);
    void set_sClass(QString&);
    void set_sSubclass(QString&);
    void set_sName(QString&);
    QString get_sOwner() const;
    QString get_sType() const;
    QString get_sClass() const;
    QString get_sSubclass() const;
    QString get_sName() const;
    QString getParamAtIt(int) const;

private:
    QString s_owner;
    QString s_type;
    QString s_class;
    QString s_subclass;
    QString s_name;
};

#endif // SPECTRUM_H
