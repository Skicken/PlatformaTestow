#pragma once
class MainMenu
{
	public:
	virtual void update() = 0;
	virtual void render() = 0;
	void setCanRoute(bool route);
	const bool CanRoute();
	private:
		bool canRoute;
};

