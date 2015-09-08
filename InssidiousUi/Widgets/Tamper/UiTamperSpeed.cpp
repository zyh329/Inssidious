#include "UiTamperSpeed.h"

UiTamperSpeed::UiTamperSpeed(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperSpeedConfig{SPEED_MAX};

	speedDescriptionLabel = new QLabel();
	speedDescriptionLabel->setText(speedDescriptionText);
	speedDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	speedDescriptionLabel->setAlignment(Qt::AlignHCenter);
	speedDescriptionLabel->setFont(moduleDescriptionFont);
	speedDescriptionLabel->setPalette(moduleTextPaletteInactive);

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet);
	buttonRight->setStyleSheet(buttonRightStyleSheet);

	buttonLeft->setText("Edge");
	buttonMiddle1->setText("3G");
	buttonMiddle2->setText("4G");
	buttonRight->setText("LTE");

	buttonLeft->setFixedSize(60, 30);
	buttonMiddle1->setFixedSize(60, 30);
	buttonMiddle2->setFixedSize(60, 30);
	buttonRight->setFixedSize(60, 30);

	buttonLeft->setFont(moduleDescriptionFont);
	buttonMiddle1->setFont(moduleDescriptionFont);
	buttonMiddle2->setFont(moduleDescriptionFont);
	buttonRight->setFont(moduleDescriptionFont);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonRight->setCheckable(true);

	speedLayout = new QGridLayout();
	speedLayout->setSpacing(0);
	
	speedLayout->addWidget(speedDescriptionLabel, 0, 0, 1, 4);

	speedLayout->addWidget(buttonLeft, 1, 0);
	speedLayout->addWidget(buttonMiddle1, 1, 1);
	speedLayout->addWidget(buttonMiddle2, 1, 2);
	speedLayout->addWidget(buttonRight, 1, 3);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonMiddle1, 1);
	buttonGroup->addButton(buttonMiddle2, 2);
	buttonGroup->addButton(buttonRight, 3);

	connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &UiTamperSpeed::onButtonClicked);

	moduleLayout->addLayout(speedLayout);
}

UiTamperSpeed::~UiTamperSpeed()
{

}

void UiTamperSpeed::toggleState(bool active)
{
	if (active)
	{
		speedDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		buttonLeft->setEnabled(true);
		buttonMiddle1->setEnabled(true);
		buttonMiddle2->setEnabled(true);
		buttonRight->setEnabled(true);
		
		if (buttonGroup->checkedId() == -1)
		{
			onButtonClicked(SPEED_LTE);
		}
	}
	else
	{
		speedDescriptionLabel->setPalette(this->moduleTextPaletteInactive);

		/* Uncheck all buttons */

		buttonGroup->setExclusive(false);
		buttonLeft->setChecked(false);
		buttonMiddle1->setChecked(false);
		buttonMiddle2->setChecked(false);
		buttonRight->setChecked(false);
		buttonGroup->setExclusive(true);

		((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_MAX;
	}
}


void UiTamperSpeed::onButtonClicked(int button)
{
	if (!selected)
	{
		emit tamperButtonClicked(this, pTamperConfig);
		return;
	}

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
