#include "UiTamperSpeed.h"

UiTamperSpeed::UiTamperSpeed(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperSpeedConfig{SPEED_MAX};

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet60);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet60);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet60);
	buttonRight->setStyleSheet(buttonRightStyleSheet60);

	buttonLeft->setText("Edge");
	buttonMiddle1->setText("3G");
	buttonMiddle2->setText("4G");
	buttonRight->setText("LTE");

	buttonLeft->setFixedSize(60, 30);
	buttonMiddle1->setFixedSize(60, 30);
	buttonMiddle2->setFixedSize(60, 30);
	buttonRight->setFixedSize(60, 30);

	buttonLeft->setFont(moduleTextFont);
	buttonMiddle1->setFont(moduleTextFont);
	buttonMiddle2->setFont(moduleTextFont);
	buttonRight->setFont(moduleTextFont);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonRight->setCheckable(true);

	speedLayout = new QGridLayout();
	speedLayout->setSpacing(0);
	
	speedLayout->addWidget(buttonLeft, 0, 0);
	speedLayout->addWidget(buttonMiddle1, 0, 1);
	speedLayout->addWidget(buttonMiddle2, 0, 2);
	speedLayout->addWidget(buttonRight, 0, 3);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonMiddle1, 1);
	buttonGroup->addButton(buttonMiddle2, 2);
	buttonGroup->addButton(buttonRight, 3);

	buttonLeft->setDisabled(true);
	buttonMiddle1->setDisabled(true);
	buttonMiddle2->setDisabled(true);
	buttonRight->setDisabled(true);

	connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &UiTamperSpeed::onButtonClicked);

	moduleLayout->addLayout(speedLayout);
}

UiTamperSpeed::~UiTamperSpeed()
{

}

void UiTamperSpeed::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		buttonLeft->setEnabled(true);
		buttonMiddle1->setEnabled(true);
		buttonMiddle2->setEnabled(true);
		buttonRight->setEnabled(true);
		

		/* Set the speed to SPEED_LTE & check the button */

		if (buttonGroup->checkedId() == -1)
		{
			buttonRight->setChecked(true);
			onButtonClicked(SPEED_LTE);
		}


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);
		
		
		/* Uncheck and disable all buttons */

		buttonGroup->setExclusive(false);

		buttonLeft->setChecked(false);
		buttonMiddle1->setChecked(false);
		buttonMiddle2->setChecked(false);
		buttonRight->setChecked(false);

		buttonLeft->setDisabled(true);
		buttonMiddle1->setDisabled(true);
		buttonMiddle2->setDisabled(true);
		buttonRight->setDisabled(true);

		buttonGroup->setExclusive(true);


		/* Set the speed back to MAX */

		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_MAX;


		/* Notify core to stop */

		emit tamperStop(this);
	}
}


void UiTamperSpeed::onButtonClicked(int button)
{
	switch (buttonGroup->checkedId())
	{
	case -1:
		/* No Button Checked */
		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_MAX;
		break;
	case SPEED_EDGE:
		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_EDGE;
		break;
	case SPEED_3G:
		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_3G;
		break;
	case SPEED_4G:
		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_4G;
		break;
	case SPEED_LTE:
		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_LTE;
		break;
	case SPEED_MAX:
	default:
		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_MAX;
		break;
	}
}
