#include "ptpch.h"
#include "StudentMenu.h"

#include "SelectList.h"

void StudentMenu::update()
{
    Mouse m = System::getMouseState();
    if(b_test.Click(m))
    {
        std::vector<std::pair<std::string, Test>> viewTests;
        std::vector < Test> tests = System::getDataInterface()->getStudentAvailableTest(System::getLoggedUser()->getID());
        for(auto t:tests)
        {
            viewTests.push_back({ t.getTestName(),t });
        }
        //System::getInstance()->setView(new SelectList<Test>(viewTests));
    }
    if(b_mail.Click(m));
    if(b_zadania.Click(m));
    if(b_wyniki.Click(m));
}

void StudentMenu::render()
{
    b_test.DrawButton();
    b_mail.DrawButton();
    b_zadania.DrawButton();
    b_wyniki.DrawButton();

    t_menu.DrawText();
    t_imie.DrawText();
    t_nazwisko.DrawText();
    t_typ.DrawText();

    t_test.DrawText();
    t_mail.DrawText();
    t_zadania.DrawText();
    t_wyniki.DrawText();
}

StudentMenu::StudentMenu()
{
    t_menu.Edit(1300, 100, 800, 100, 100, "Menu");
    t_imie.Edit(100, 100, 600, 100, 50, System::getLoggedUser()->getName());
    t_nazwisko.Edit(100, 165, 600, 100, 50, System::getLoggedUser()->getSurname());
    t_typ.Edit(100, 220, 600, 100, 50, ExternalData::EnumToString(System::getLoggedUser()->getType()));

    t_test.Edit(1330, 330, 200, 40, 40, "Test");
    t_mail.Edit(1330, 530, 200, 40, 40, "Mail");
    t_zadania.Edit(1330, 730, 200, 40, 40, "Zadania");
    t_wyniki.Edit(1330, 700, 200, 40, 40, "Wyniki");

    b_test.Edit(1300, 300, 400, 100);
    b_mail.Edit(1300, 500, 400, 100);
    b_zadania.Edit(1300, 700, 400, 100);
    b_wyniki.Edit(1300, 670, 400, 100);



}