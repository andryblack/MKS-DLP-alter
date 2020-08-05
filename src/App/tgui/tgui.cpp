/*******************************************************************************
*
*     Base user interface for LCD with touch
*
********************************************************************************/

#include "tgui.h"
#include "tgui_defaultfuncs.h"
#include "tgui_langscreenfuncs.h"
#include "tgui_infoscreenfuncs.h"
#include "tgui_mainscreenfuncs.h"

__no_init uint8_t 		tguiDBuff[UIDBUFF_SIZE];
__no_init uint8_t		tguiFBuff[UIFBUFF_SIZE];
__no_init FIL			tguiFile @ "CCMRAM";
__no_init TCHAR			tfname[512] @ "CCMRAM";

TG_CONFIG		tguiDefaultConfig;

TG_BUTTON		tguiScrMainButtons[TG_BTN_CNT_SCREEN_MAIN];
TG_SCREEN		tguiScreenMain;

TG_BUTTON		tguiScrServiceButtons[TG_BTN_CNT_SCREEN_SERVICE];
TG_SCREEN		tguiScreenService;

TG_BUTTON		tguiScrLanguageButtons[TG_BTN_CNT_SCREEN_LANGUAGE];
TG_SCREEN		tguiScreenLanguage;

TG_BUTTON		tguiScrInfoButtons[TG_BTN_CNT_SCREEN_INFO];
TG_SCREEN		tguiScreenInfo;

TG_BUTTON		tguiScrMovezButtons[TG_BTN_CNT_SCREEN_MOVEZ];
TG_SCREEN		tguiScreenMovez;



TG_SCREEN		*tguiActiveScreen;




uint8_t		TGUI_PointInRect(TOUCH_POINT *pt, TG_RECT *rc)
{
	if (pt->xc >= rc->left && pt->xc <= rc->right)
	{
		if (pt->yc >= rc->top && pt->yc <= rc->bottom)
			return 1;
	}
	
	return 0;
}
//==============================================================================










void		TGUI_Init()
{
	TG_CONFIG		*tgc;
	TG_SCREEN		*tgs;
	TG_BUTTON		*tgb;
	
	
	uint8_t			bi = 0;
	int16_t			bx, by, bw, bh;
	
	
	tguiActiveScreen = &tguiScreenMain;
	
	// DEFAULT CONFIG
	tgc = &tguiDefaultConfig;
	memset((void*)tgc, 0, sizeof(TG_CONFIG));
	
	tgc->scrnametextcolor = LCDUI_RGB(0xBAC5D5);
	tgc->scrtextcolor = LCDUI_RGB(0x00272E);
	tgc->scrbackcolor = LCDUI_RGB(0x648E62);
	tgc->scrfont = LCDUI_FONT_H18;
	tgc->scrnamefont = LCDUI_FONT_H24BOLD;

	tgc->btntextcolor_en = LCDUI_RGB(0x00272E);
	tgc->btntextcolor_press = LCDUI_RGB(0x8080FF);
	tgc->btntextcolor_dis = LCDUI_RGB(0x404040);
	tgc->btntextcolor_act = LCDUI_RGB(0x8080FF);
	tgc->btnbackcolor_en = LCDUI_RGB(0xA6BFCB);
	tgc->btnbackcolor_press = LCDUI_RGB(0xA6BFCB);
	tgc->btnbackcolor_dis = LCDUI_RGB(0xCBCBCB);
	tgc->btnbackcolor_act = LCDUI_RGB(0xA6BFCB);
	tgc->btnfont = LCDUI_FONT_H24BOLD;
	
	
	_tgui_ScreenTimeInit();
	
	
	// -------------------- Main Screen elements -----------------------
{
	bi = 0;
	// PRINT button
	tgb = &(tguiScrMainButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->position = {15, 100, 465, 165};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR_PRINT;
	tgb->textposition = {115, 103, 450, 162};
	tgb->font = tgc->btnfont;
	tgb->textcolor_en = tgc->btntextcolor_en;
	tgb->textcolor_press = tgc->btntextcolor_press;
	tgb->textcolor_dis = tgc->btntextcolor_dis;
	tgb->backcolor_en = tgc->btnbackcolor_en;
	tgb->backcolor_press = tgc->btnbackcolor_press;
	tgb->backcolor_dis = tgc->btnbackcolor_dis;
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_NONE;
	tgb->options.repaintonpress = 1;
	
	tgb->textoptions.textalign_h = HTA_CENTER;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
	tgb->funcs._call_press = NULL;
	tgb->funcs._call_process = _tgui_DefaultButtonProcess;

	tgb->parentscreen = &tguiScreenMain;
	tgb->childscreen = NULL;

	// INFO button
	tgb = &(tguiScrMainButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrMainButtons[0]), sizeof(TG_BUTTON));
	
	tgb->position = {245, 185, 465, 250};

	tgb->text = LSTR_INFO;
	tgb->textposition = {320, 188, 460, 247};

	tgb->funcs._call_press = (pressfunc)BTNA_GOCHILDSCR;

	tgb->childscreen = (void*)&tguiScreenInfo;

	// SERVICE button
	tgb = &(tguiScrMainButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrMainButtons[0]), sizeof(TG_BUTTON));
	
	tgb->position = {15, 185, 235, 250};

	tgb->text = LSTR_SERVICE;
	tgb->textposition = {85, 188, 230, 247};

	tgb->funcs._call_press = (pressfunc)BTNA_GOCHILDSCR;

	tgb->childscreen = (void*)&tguiScreenService;

	// TIME text-button
	tgb = &(tguiScrMainButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->button_id = TG_TIMEBUTTON_ID;
	
	tgb->position = {6, 4, 169, 29};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR____;
	tgb->textposition = {6, 4, 169, 29};
	tgb->font = LCDUI_FONT_H24;
	tgb->textcolor_en = LCDUI_RGB(0xBAC5D5);
	tgb->textcolor_press = LCDUI_RGB(0xBAC5D5);
	tgb->textcolor_dis = LCDUI_RGB(0xBAC5D5);
	tgb->backcolor_en = LCDUI_RGB(0x0000);
	tgb->backcolor_press = LCDUI_RGB(0x0000);
	tgb->backcolor_dis = LCDUI_RGB(0x0000);
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_FILL;
	tgb->options.repaintonpress = 0;
	
	tgb->textoptions.textalign_h = HTA_CENTER;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_ScreenTimePaint;
	tgb->funcs._call_press = NULL;
	tgb->funcs._call_process = _tgui_ScreenTimeProcess;

	tgb->parentscreen = &tguiScreenMain;
	tgb->childscreen = NULL;

	
	
	// MAIN SCREEN
	tgs = &tguiScreenMain;
	memset((void*)tgs, 0, sizeof(TG_SCREEN));
	
	tgs->bgimagename = FNAME_BKGR_MAIN;
	tgs->prevscreen = NULL;

	tgs->name = LSTR_MAINMENU;
	tgs->nameposition = {205, 3, 475, 30};
	tgs->nameoptions.textalign_h = HTA_CENTER;
	tgs->nameoptions.textalign_v = VTA_CENTER;

	tgs->btns_count = TG_BTN_CNT_SCREEN_MAIN;
	tgs->buttons = tguiScrMainButtons;

	tgs->font = tgc->scrfont;
	tgs->namefont = tgc->scrnamefont;
	tgs->textcolor = tgc->scrtextcolor;
	tgs->nametextcolor = tgc->scrnametextcolor;
	tgs->backcolor = tgc->scrbackcolor;

	tgs->funcs._callpaint = _tgui_DefaultScreenPaint;
	tgs->funcs._process = _tgui_DefaultScreenProcess;
	
}



	// -------------------- Service Screen elements -----------------------
{
	bi = 0;
	// BACK button
	tgb = &(tguiScrServiceButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->position = {4, 4, 167, 49};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR_BACK;
	tgb->textposition = {54, 6, 165, 47};
	tgb->font = tgc->btnfont;
	tgb->textcolor_en = LCDUI_RGB(0x074B19);
	tgb->textcolor_press = tgc->btntextcolor_press;
	tgb->textcolor_dis = tgc->btntextcolor_dis;
	tgb->backcolor_en = tgc->btnbackcolor_en;
	tgb->backcolor_press = tgc->btnbackcolor_press;
	tgb->backcolor_dis = tgc->btnbackcolor_dis;
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_NONE;
	tgb->options.repaintonpress = 1;

	tgb->textoptions.textalign_h = HTA_CENTER;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
	tgb->funcs._call_press = (pressfunc)BTNA_GOPREVSCR;
	tgb->funcs._call_process = _tgui_DefaultButtonProcess;

	tgb->parentscreen = &tguiScreenService;
	tgb->childscreen = NULL;

	// LANGUAGE button
	tgb = &(tguiScrServiceButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrServiceButtons[0]), sizeof(TG_BUTTON));
	
	tgb->position = {15, 65, 235, 130};

	tgb->textcolor_en = tgc->btntextcolor_en;

	tgb->text = LSTR_LANGUAGE;
	tgb->textposition = {80, 67, 230, 128};

	tgb->funcs._call_press = (pressfunc)BTNA_GOCHILDSCR;

	tgb->childscreen = &tguiScreenLanguage;
	
	
	// MOVEZ button
	tgb = &(tguiScrServiceButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrServiceButtons[0]), sizeof(TG_BUTTON));
	
	tgb->position = {245, 65, 464, 130};

	tgb->textcolor_en = tgc->btntextcolor_en;

	tgb->text = LSTR_MOVEZ;
	tgb->textposition = {316, 67, 462, 128};

	tgb->funcs._call_press = (pressfunc)BTNA_GOCHILDSCR;

	tgb->childscreen = &tguiScreenMovez;
	
	
	// SERVICE SCREEN
	tgs = &tguiScreenService;
	memset((void*)tgs, 0, sizeof(TG_SCREEN));
	
	tgs->bgimagename = FNAME_BKGR_SERVICE;
	tgs->prevscreen = &tguiScreenMain;

	tgs->name = LSTR_INFO;
	tgs->nameposition = {205, 3, 475, 30};
	tgs->nameoptions.textalign_h = HTA_CENTER;
	tgs->nameoptions.textalign_v = VTA_CENTER;

	tgs->btns_count = TG_BTN_CNT_SCREEN_SERVICE;
	tgs->buttons = tguiScrServiceButtons;

	tgs->font = tgc->scrfont;
	tgs->namefont = tgc->scrnamefont;
	tgs->textcolor = tgc->scrtextcolor;
	tgs->nametextcolor = tgc->scrnametextcolor;
	tgs->backcolor = tgc->scrbackcolor;

	tgs->funcs._callpaint = _tgui_DefaultScreenPaint;
	tgs->funcs._process = _tgui_DefaultScreenProcess;
	
}



	// -------------------- Language Screen elements -----------------------
{
	bi = 0;
	// LANGUAGE buttons
	char	*txt;
	for (bi = 0; bi < TG_BTN_CNT_SCREEN_LANGUAGE - 1; bi++)
	{
		tgb = &(tguiScrLanguageButtons[bi]);
		memset((void*)tgb, 0, sizeof(TG_BUTTON));
		
		tgb->button_id = bi;
		
		tgb->position = {(int16_t)25, (int16_t)(65 + (bi * 50)), (int16_t)455, (int16_t)(110 + (bi * 50))};

		tgb->bgimagename_en = NULL;
		tgb->bgimagename_press = NULL;
		tgb->bgimagename_dis = NULL;

		txt = LANG_GetLanguageName(bi);
		tgb->text = (LNG_STRING_ID)((DWORD)txt);
		tgb->textposition = {(int16_t)55, (int16_t)(67 + (bi * 50)), (int16_t)425, (int16_t)(108 + (bi * 50))};
		tgb->font = tgc->btnfont;

		tgb->textcolor_en = tgc->btntextcolor_en;
		tgb->textcolor_press = tgc->btntextcolor_press;
		tgb->textcolor_dis = tgc->btntextcolor_dis;
		tgb->backcolor_en = tgc->btnbackcolor_en;
		tgb->backcolor_press = tgc->btnbackcolor_press;
		tgb->backcolor_dis = tgc->btnbackcolor_dis;
		
		tgb->options.disabled = 0;
		tgb->options.bgpaint = BGP_NONE;
		tgb->options.repaintonpress = 1;
		
		tgb->textoptions.textalign_h = HTA_CENTER;
		tgb->textoptions.textalign_v = VTA_CENTER;

		tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
		tgb->funcs._call_press = _tgui_LanguageButtonPress;		// must not be zero or a predefined value
		tgb->funcs._call_process = _tgui_DefaultButtonProcess;

		tgb->parentscreen = &tguiScreenLanguage;
		tgb->childscreen = NULL;
	}
	
	// BACK button
	tgb = &(tguiScrLanguageButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->position = {4, 4, 167, 49};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR_BACK;
	tgb->textposition = {54, 6, 165, 47};
	tgb->font = tgc->btnfont;
	tgb->textcolor_en = LCDUI_RGB(0x074B19);
	tgb->textcolor_press = tgc->btntextcolor_press;
	tgb->textcolor_dis = tgc->btntextcolor_dis;
	tgb->backcolor_en = tgc->btnbackcolor_en;
	tgb->backcolor_press = tgc->btnbackcolor_press;
	tgb->backcolor_dis = tgc->btnbackcolor_dis;
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_NONE;
	tgb->options.repaintonpress = 1;
	
	tgb->textoptions.textalign_h = HTA_CENTER;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
	tgb->funcs._call_press = (pressfunc)BTNA_GOPREVSCR;
	tgb->funcs._call_process = _tgui_DefaultButtonProcess;

	tgb->parentscreen = &tguiScreenLanguage;
	tgb->childscreen = NULL;

	
	// LANGUAGE SCREEN
	tgs = &tguiScreenLanguage;
	memset((void*)tgs, 0, sizeof(TG_SCREEN));
	
	tgs->bgimagename = FNAME_BKGR_LANGUAGE;
	tgs->prevscreen = &tguiScreenService;

	tgs->name = LSTR_LANGUAGE;
	tgs->nameposition = {205, 3, 475, 30};
	tgs->nameoptions.textalign_h = HTA_CENTER;
	tgs->nameoptions.textalign_v = VTA_CENTER;

	tgs->btns_count = TG_BTN_CNT_SCREEN_LANGUAGE;
	tgs->buttons = tguiScrLanguageButtons;

	tgs->font = tgc->scrfont;
	tgs->namefont = tgc->scrnamefont;
	tgs->textcolor = tgc->scrtextcolor;
	tgs->nametextcolor = tgc->scrnametextcolor;
	tgs->backcolor = tgc->scrbackcolor;

	tgs->funcs._callpaint = _tgui_DefaultScreenPaint;
	tgs->funcs._process = _tgui_DefaultScreenProcess;
	
}



	// -------------------- Info Screen elements -----------------------
{
	bi = 0;
	// BACK button
	tgb = &(tguiScrInfoButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->position = {4, 4, 167, 49};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR_BACK;
	tgb->textposition = {54, 6, 165, 47};
	tgb->font = tgc->btnfont;
	tgb->textcolor_en = LCDUI_RGB(0x074B19);
	tgb->textcolor_press = tgc->btntextcolor_press;
	tgb->textcolor_dis = tgc->btntextcolor_dis;
	tgb->backcolor_en = tgc->btnbackcolor_en;
	tgb->backcolor_press = tgc->btnbackcolor_press;
	tgb->backcolor_dis = tgc->btnbackcolor_dis;
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_NONE;
	tgb->options.repaintonpress = 1;
	
	tgb->textoptions.textalign_h = HTA_CENTER;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
	tgb->funcs._call_press = (pressfunc)BTNA_GOPREVSCR;
	tgb->funcs._call_process = _tgui_DefaultButtonProcess;

	tgb->parentscreen = &tguiScreenInfo;
	tgb->childscreen = NULL;

	
	bx = 25;
	by = 65;
	bw = 50;
	bh = 30;
	// VERSION_TEXT button
	tgb = &(tguiScrInfoButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR_VERSION;
	tgb->textposition = {(int16_t)(bx+10), by, (int16_t)(bx+bw), (int16_t)(by+bh)};
	tgb->font = LCDUI_FONT_H24;
	tgb->textcolor_en = LCDUI_RGB(0x00272E);
	tgb->textcolor_press = tgc->btntextcolor_press;
	tgb->textcolor_dis = tgc->btntextcolor_dis;
	tgb->backcolor_en = tgc->btnbackcolor_en;
	tgb->backcolor_press = tgc->btnbackcolor_press;
	tgb->backcolor_dis = tgc->btnbackcolor_dis;
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_NONE;
	tgb->options.repaintonpress = 0;
	
	tgb->textoptions.textalign_h = HTA_LEFT;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
	tgb->funcs._call_press = NULL;

	tgb->parentscreen = &tguiScreenInfo;
	tgb->childscreen = NULL;
	tgb->funcs._call_process = _tgui_DefaultButtonProcess;
	by += bh;

	// LIGHTTIME_TEXT button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));

	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR_LIGHTTIME;
	tgb->textposition = {(int16_t)(bx+10), by, (int16_t)(bx+bw), (int16_t)(by+bh)};
	by += bh;

	// FANSTIME_TEXT button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR_FANSTIME;
	tgb->textposition = {(int16_t)(bx+10), by, (int16_t)(bx+bw), (int16_t)(by+bh)};
	by += bh;

	// URL_TEXT button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR_URL;
	tgb->textposition = {(int16_t)(bx+10), by, (int16_t)(bx+bw), (int16_t)(by+bh)};
	by += bh;

	// UIAUTHOR_TEXT button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR_UIAUTHOR;
	tgb->textposition = {(int16_t)(bx+10), by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	bx = 76;
	by = 65;
	bw = 380;
	// VERSION_VAL button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR____;
	tgb->textposition = {bx, by, (int16_t)(bx+bw-10), (int16_t)(by+bh)};
	tgb->textoptions.textalign_h = HTA_RIGHT;
	tgb->textcolor_en = LCDUI_RGB(0x0060A0);

	tgb->funcs._call_paint = _tgui_InfoScreenVersionPaint;
	by += bh;

	// LIGHTTIME_VAL button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR____;
	tgb->textposition = {bx, by, (int16_t)(bx+bw-10), (int16_t)(by+bh)};

	tgb->funcs._call_paint = _tgui_InfoScreenLightTimePaint;
	by += bh;

	// FANSTIME_VAL button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR____;
	tgb->textposition = {bx, by, (int16_t)(bx+bw-10), (int16_t)(by+bh)};

	tgb->funcs._call_paint = _tgui_InfoScreenFansTimePaint;
	by += bh;

	// URL_VAL button
	by += 4;
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR____;
	tgb->textposition = {bx, by, (int16_t)(bx+bw-10), (int16_t)(by+bh)};
	tgb->font = LCDUI_FONT_H18;

	tgb->funcs._call_paint = _tgui_InfoScreenURLPaint;
	by += bh;

	// UIAUTHOR_VAL button
	tgb = &(tguiScrInfoButtons[bi++]);
	memcpy((void*)tgb, &(tguiScrInfoButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->position = {bx, by, (int16_t)(bx+bw), (int16_t)(by+bh)};

	tgb->text = LSTR____;
	tgb->textposition = {bx, by, (int16_t)(bx+bw-10), (int16_t)(by+bh)};

	tgb->funcs._call_paint = _tgui_InfoScreenUIAuthorPaint;


	
	// INFO SCREEN
	tgs = &tguiScreenInfo;
	memset((void*)tgs, 0, sizeof(TG_SCREEN));
	
	tgs->bgimagename = FNAME_BKGR_INFO;
	tgs->prevscreen = &tguiScreenMain;

	tgs->name = LSTR_INFO;
	tgs->nameposition = {205, 3, 475, 30};
	tgs->nameoptions.textalign_h = HTA_CENTER;
	tgs->nameoptions.textalign_v = VTA_CENTER;

	tgs->btns_count = TG_BTN_CNT_SCREEN_INFO;
	tgs->buttons = tguiScrInfoButtons;

	tgs->font = tgc->scrfont;
	tgs->namefont = tgc->scrnamefont;
	tgs->textcolor = tgc->scrtextcolor;
	tgs->nametextcolor = tgc->scrnametextcolor;
	tgs->backcolor = tgc->scrbackcolor;

	tgs->funcs._callpaint = _tgui_DefaultScreenPaint;
	tgs->funcs._process = _tgui_DefaultScreenProcess;
	
}



	// -------------------- MoveZ Screen elements -----------------------
{
	bi = 0;
	// BACK button
	tgb = &(tguiScrMovezButtons[bi++]);
	memset((void*)tgb, 0, sizeof(TG_BUTTON));
	
	tgb->position = {4, 4, 167, 49};

	tgb->bgimagename_en = NULL;
	tgb->bgimagename_press = NULL;
	tgb->bgimagename_dis = NULL;

	tgb->text = LSTR_BACK;
	tgb->textposition = {54, 6, 165, 47};
	tgb->font = tgc->btnfont;
	tgb->textcolor_en = LCDUI_RGB(0x074B19);
	tgb->textcolor_press = tgc->btntextcolor_press;
	tgb->textcolor_dis = tgc->btntextcolor_dis;
	tgb->backcolor_en = tgc->btnbackcolor_en;
	tgb->backcolor_press = tgc->btnbackcolor_press;
	tgb->backcolor_dis = tgc->btnbackcolor_dis;
	
	tgb->options.disabled = 0;
	tgb->options.bgpaint = BGP_NONE;
	tgb->options.repaintonpress = 1;
	
	tgb->textoptions.textalign_h = HTA_CENTER;
	tgb->textoptions.textalign_v = VTA_CENTER;

	tgb->funcs._call_paint = _tgui_DefaultButtonPaint;
	tgb->funcs._call_press = (pressfunc)BTNA_GOPREVSCR;
	tgb->funcs._call_process = _tgui_DefaultButtonProcess;

	tgb->parentscreen = &tguiScreenMovez;
	tgb->childscreen = NULL;

	// 10mm button
	tgb = &(tguiScrMovezButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrMovezButtons[0]), sizeof(TG_BUTTON));
	
	tgb->group_id = 1;
	tgb->button_id = 0;
	
	tgb->position = {16, 65, 115, 114};

	tgb->textcolor_en = tgc->btntextcolor_en;
	tgb->textcolor_act = LCDUI_RGB(0xC80000);

	tgb->text = LSTR_10MM;
	tgb->textposition = {16, 65, 115, 114};

	tgb->funcs._call_press = NULL;

	tgb->childscreen = NULL;

	// 1mm button
	tgb = &(tguiScrMovezButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrMovezButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->button_id = 1;

	tgb->position = {132, 65, 231, 114};

	tgb->textcolor_en = tgc->btntextcolor_en;

	tgb->text = LSTR_1MM;
	tgb->textposition = {132, 65, 231, 114};

	tgb->funcs._call_press = NULL;

	tgb->childscreen = NULL;

	// 0.2mm button
	tgb = &(tguiScrMovezButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrMovezButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->button_id = 2;
	tgb->options.active = 1;

	tgb->position = {248, 65, 347, 114};

	tgb->textcolor_en = tgc->btntextcolor_en;

	tgb->text = LSTR_02MM;
	tgb->textposition = {248, 65, 347, 114};

	tgb->funcs._call_press = NULL;

	tgb->childscreen = NULL;

	// 0.05mm button
	tgb = &(tguiScrMovezButtons[bi++]);
	memcpy((void*)tgb, (void*)(&tguiScrMovezButtons[bi-2]), sizeof(TG_BUTTON));
	
	tgb->button_id = 3;
	tgb->options.active = 0;

	tgb->position = {364, 65, 463, 114};

	tgb->textcolor_en = tgc->btntextcolor_en;

	tgb->text = LSTR_005MM;
	tgb->textposition = {364, 65, 463, 114};

	tgb->funcs._call_press = NULL;

	tgb->childscreen = NULL;


	// MOVEZ SCREEN
	tgs = &tguiScreenMovez;
	memset((void*)tgs, 0, sizeof(TG_SCREEN));
	
	tgs->bgimagename = FNAME_BKGR_MOVEZ;
	tgs->prevscreen = &tguiScreenService;

	tgs->name = LSTR_MOVEZ;
	tgs->nameposition = {205, 3, 475, 30};
	tgs->nameoptions.textalign_h = HTA_CENTER;
	tgs->nameoptions.textalign_v = VTA_CENTER;

	tgs->btns_count = TG_BTN_CNT_SCREEN_MOVEZ;
	tgs->buttons = tguiScrMovezButtons;

	tgs->font = tgc->scrfont;
	tgs->namefont = tgc->scrnamefont;
	tgs->textcolor = tgc->scrtextcolor;
	tgs->nametextcolor = tgc->scrnametextcolor;
	tgs->backcolor = tgc->scrbackcolor;

	tgs->funcs._callpaint = _tgui_DefaultScreenPaint;
	tgs->funcs._process = _tgui_DefaultScreenProcess;
	
}



}
//==============================================================================



void		TGUI_DrawLogo()
{
	_tgui_DrawFileCimgBackground(FNAME_LOGO);
}
//==============================================================================




// Forced repaint current screen
void		TGUI_ForceRepaint()
{
	if (tguiActiveScreen->funcs._callpaint != NULL)
		tguiActiveScreen->funcs._callpaint(tguiActiveScreen, NULL);
}
//==============================================================================




// Current screen periodical process handling (check for changes, touch pressed, etc)
void		TGUI_Process()
{
	if (tguiActiveScreen->funcs._process != NULL)
		tguiActiveScreen->funcs._process(tguiActiveScreen, NULL);
}
//==============================================================================




