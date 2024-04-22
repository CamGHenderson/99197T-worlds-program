#include "ScuffedUI.h"

#include "api.h"

uint16_t selection = NONE;
uint8_t color = RED;

lv_obj_t* blueBtn = NULL;
lv_obj_t* redBtn = NULL;

void displayTest()
{
	lv_obj_t* label = lv_label_create(lv_scr_act(), NULL);
  	lv_label_set_text(label, "Test Selection Menu");
  	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
  	
  	lv_obj_t* btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(btn1, 200, 50);
	lv_obj_set_x(btn1, LV_HOR_RES / 2 - 100);
	lv_obj_set_y(btn1, LV_VER_RES / 2 - 25);
	lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
	
	label = lv_label_create(btn1, NULL);
 	lv_label_set_text(label, "Test Button");
}

lv_res_t selectCloseAuto(lv_obj_t* btn)
{
	if(selection == NONE)
	{
		selection = UI_CLOSE_AUTO;
		lv_btn_toggle(btn);
	}
	return LV_RES_OK; 
}

lv_res_t selectFarAuto(lv_obj_t* btn)
{
	if(selection == NONE)
	{
		selection = UI_FAR_AUTO;
		lv_btn_toggle(btn);
	}
	return LV_RES_OK;
}

lv_res_t selectAutoSkills(lv_obj_t* btn)
{
	if(selection == NONE)
	{
		selection = UI_AUTO_SKILLS;
		lv_btn_toggle(btn);
	}
	return LV_RES_OK;
}

lv_res_t selectBlue(lv_obj_t* btn)
{
	if(color != BLUE && selection == NONE)
	{
		color = BLUE;
		lv_btn_toggle(blueBtn);
		lv_btn_toggle(redBtn);
	}
	
	return LV_RES_OK;
}

lv_res_t selectRed(lv_obj_t* btn)
{
	if(color != RED && selection == NONE)
	{
		color = RED;
		lv_btn_toggle(blueBtn);
		lv_btn_toggle(redBtn);
	}

	return LV_RES_OK;
}

// This is hitler's creation
void displayAutoMenu()
{
	lv_obj_t* label = lv_label_create(lv_scr_act(), NULL);
  	lv_label_set_text(label, "Auton Program Menu (Fuck you!)");
  	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
 	
 	// TODO wrap buttons into function
 	// Thanks past me this code is roughly a year old and I still haven't fixed it //*two years
 	// and I'm still not gonna fix it
  	lv_obj_t* closeAuto = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(closeAuto, 200, 50);
	lv_obj_set_x(closeAuto, LV_HOR_RES / 2 + 10);
	lv_obj_set_y(closeAuto, LV_VER_RES / 2 - 60);
	lv_obj_set_free_num(closeAuto, 1);
	lv_btn_set_action(closeAuto, LV_BTN_ACTION_CLICK, selectCloseAuto);
	
  	// TODO fix backwards ui garbage
	lv_obj_t* btn1Label = lv_label_create(closeAuto, NULL);
 	lv_label_set_text(btn1Label, "Descore Auton");
 	
 	lv_obj_t* farAuto = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(farAuto, 200, 50);
	lv_obj_set_x(farAuto, LV_HOR_RES / 2 + 10);
	lv_obj_set_y(farAuto, LV_VER_RES / 2);
	lv_obj_set_free_num(farAuto, 1);
	lv_btn_set_action(farAuto, LV_BTN_ACTION_CLICK, selectFarAuto);
	
	lv_obj_t* btn2Label = lv_label_create(farAuto, NULL);
 	lv_label_set_text(btn2Label, "Far Side");
	
	lv_obj_t* autoSkills = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(autoSkills, 200, 50);
	lv_obj_set_x(autoSkills, LV_HOR_RES / 2 + 10);
	lv_obj_set_y(autoSkills, LV_VER_RES / 2 + 60);
	lv_obj_set_free_num(autoSkills, 1);
	lv_btn_set_action(autoSkills, LV_BTN_ACTION_CLICK, selectAutoSkills);
	
	lv_obj_t* skillsButtonLabel = lv_label_create(autoSkills, NULL);
 	lv_label_set_text(skillsButtonLabel, "Auto Skills");
 	
 	redBtn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(redBtn, 200, 50);
	lv_obj_set_x(redBtn, LV_HOR_RES / 2 - 210);
	lv_obj_set_y(redBtn, LV_VER_RES / 2 - 60);
	lv_obj_set_free_num(redBtn, 1);
	lv_btn_set_action(redBtn, LV_BTN_ACTION_CLICK, selectRed);
	
	lv_obj_t* redLabel = lv_label_create(redBtn, NULL);
 	lv_label_set_text(redLabel, "Red");
	lv_btn_toggle(redBtn);
	
	blueBtn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(blueBtn, 200, 50);
	lv_obj_set_x(blueBtn, LV_HOR_RES / 2 - 210);
	lv_obj_set_y(blueBtn, LV_VER_RES / 2);
	lv_obj_set_free_num(blueBtn, 1);
	lv_btn_set_action(blueBtn, LV_BTN_ACTION_CLICK, selectBlue);
	
	lv_obj_t* blueLabel = lv_label_create(blueBtn, NULL);
 	lv_label_set_text(blueLabel, "Blue");
}

uint16_t getUISelection() { return selection; }
uint8_t getUIColor() { return color; }
