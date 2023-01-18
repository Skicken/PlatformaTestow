#pragma once
#pragma once
#include "View.h"
#include <UI/Text.h>
#include <UI/Button.h>
#include <System.h>
class TeacherMenu :
    public View
{

public:
    virtual void update() override;
    virtual void render() override;
    TeacherMenu();
private:
    Text t_menu;
    Text t_imie, t_nazwisko, t_typ;

    Text t_test;
    Text t_mail;
    Text t_zadania;
    Text t_wyniki;
    Text t_obecnosc;

    Button b_test;
    Button b_mail;
    Button b_zadania;
    Button b_wyniki;
    Button b_obecnosc;
};