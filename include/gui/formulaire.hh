#ifndef __HH_FORM__
#define  __HH_FORM__

#include <QWidget>
#include <QVBoxLayout>
#include <vector>

class formulaire : public QWidget
{
private:
	std::vector<QWidget*> widgets;

public:
	formulaire();
	~formulaire();
	
};


#endif