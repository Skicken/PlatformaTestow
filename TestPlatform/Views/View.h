#pragma once
class View
{
	public:
		///program konsolowy musi blokowaæ program poleceniem cin
		///czekaæ az uzytkownik cos wpisze, czasem wyjscie wyprowadzic
		/// trzeba bedzie w update
		virtual void update() = 0;
		virtual void render() = 0;
};

