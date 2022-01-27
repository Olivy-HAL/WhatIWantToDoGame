#pragma once
#include <vector>
#include <memory>

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Actor/CDisplay2DActor.h"

#include "CPauseUI.h"

class CPause :public CActor
{
public:
	enum SelectButton
	{
		RESUME,
		RESTART,
		CONFIG,
		END
	};

private:
	CDisplay2DActor* mBackground;

	std::vector<std::unique_ptr<CPauseUI>> mButtons;

	CDisplay2DActor* mResumeButton;
	CDisplay2DActor* mRestartButton;
	CDisplay2DActor* mConfigButton;
	CDisplay2DActor* mEndButton;

	SelectButton mSelect = SelectButton::RESUME;
public:
	CPause(ILevel& owner);

	void Select(int num);
	void Cancel();
	SelectButton GetSelect() { return mSelect; }

	void Tick()override;
};