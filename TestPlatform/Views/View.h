#pragma once
class View
{
	public:
		///program konsolowy musi blokowa� program poleceniem cin
		///czeka� az uzytkownik cos wpisze, czasem wyjscie wyprowadzic
		/// trzeba bedzie w update
		virtual void update() = 0;
		virtual void render() = 0;
};

