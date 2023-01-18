#include "ptpch.h"
#include "MainMenu.h"

void MainMenu::setCanRoute(bool route)
{
    this->canRoute = route;
}

const bool MainMenu::CanRoute()
{
    return canRoute;
}
