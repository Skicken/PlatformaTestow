#pragma once
class View
{
	public:
	virtual ~View() = default;
	virtual void update() = 0;
	virtual void render() = 0;
};

