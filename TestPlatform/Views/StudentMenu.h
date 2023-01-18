#pragma once
#include "View.h"
#include <UI/Text.h>
#include <UI/Button.h>
#include <System.h>
class StudentMenu :
    public View
{

public:
    virtual void update() override;
    virtual void render() override;
    StudentMenu();
private:
    Text t_menu;
    Text t_imie, t_nazwisko, t_typ;

    Text t_test;
    Text t_mail;
    Text t_zadania;
    Text t_wyniki;

    Button b_test;
    Button b_mail;
    Button b_zadania;
    Button b_wyniki;
};