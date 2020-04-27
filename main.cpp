#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "LibGwentDrawSim.h"

HINSTANCE hInst;

char deck_path[MAX_PATH];

GWENT_TYPE deck;
GWENT_TYPE hand;

int card_names [] =
{
    IDC_CARD_NAME_1, IDC_CARD_NAME_2, IDC_CARD_NAME_3, IDC_CARD_NAME_4, IDC_CARD_NAME_5,
    IDC_CARD_NAME_6, IDC_CARD_NAME_7, IDC_CARD_NAME_8, IDC_CARD_NAME_9, IDC_CARD_NAME_10,
};

void open_deck(HWND hwnd, char * ret_path)
{
    OPENFILENAME OFN;
    char str[300];
    char lpstrFile[MAX_PATH]="";

	// player 1
	gwent_set_player(0);

    memset(&OFN, 0, sizeof(OPENFILENAME));
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner=hwnd;
    OFN.lpstrFilter="Deck Text File(*.*)\0*.*\0Text File\0*.txt\0";
    OFN.lpstrFile=lpstrFile;
    OFN.nMaxFile=256;
    OFN.lpstrInitialDir="c:\\";

    if (GetOpenFileName(&OFN)!=0)
    {
        SetDlgItemText(hwnd, IDC_EDIT_DECK_PATH, OFN.lpstrFile);
        memcpy(ret_path, OFN.lpstrFile, MAX_PATH);
    }
}

void update_ui(HWND hwnd)
{
    // clear card name
    for (int i = 0; i < 10; i++)
        SetDlgItemText(hwnd, card_names[i], "");

	hand = gwent_get_hand();
    for(int i = 0; i < hand.size(); i++)
    {
        char * card_str = new char[hand.at(i).length()];
        char * p;
        memcpy(card_str, hand.at(i).c_str(), hand.at(i).length());
        p = strtok(card_str, "@");
        SetDlgItemText(hwnd, card_names[i], p);
        delete card_str;
    }
	deck = gwent_get_deck();
    SetDlgItemInt(hwnd, IDC_CARD_COUNT, deck.size(), 0);
}

void get_card_img_url(int index, char * url)
{
        char * p;
        char card_str[MAX_PATH];
		hand = gwent_get_hand();
        sprintf(card_str, "%s", hand.at(index).c_str());
        printf("%s",  card_str);
        p = strtok(card_str, "@");
        p = strtok(NULL, "@");
        memcpy(url, p, strlen(p));
        url[strlen(url)] = '\0';
}

int show_card_info(int card_no)
{
    char card_url[MAX_PATH] = {0, };
	
	hand = gwent_get_hand();
    if(hand.size() == 0)
        return -1;

    if(card_no > hand.size())
        return -1;

    memset(card_url, 0, MAX_PATH);
    get_card_img_url(card_no, card_url);
    //printf("%s", card_url);
    ShellExecuteA(NULL, "open",  card_url, NULL, NULL, SW_SHOWNORMAL);
    return 1;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


    switch(uMsg)
    {
    case WM_INITDIALOG:
        {
        }
        return TRUE;

    case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case IDC_OPEN_DECK:
				gwent_clear_all();
				deck = gwent_get_deck();
				hand = gwent_get_hand();
                memset(deck_path, 0, MAX_PATH);
                open_deck(hwndDlg, deck_path);
                deck.clear();
                hand.clear();
                gwent_loaddeck(deck_path);
                gwent_draw(10);
                update_ui(hwndDlg);
                break;
            case IDC_REPLAY:
				gwent_clear_all();
                deck.clear();
                hand.clear();
                gwent_loaddeck(deck_path);
                gwent_draw(10);
                update_ui(hwndDlg);
                break;
            case IDC_RESHUFFLE:
                gwent_shuffle_deck();
                break;
            case IDC_DRAW:
                if(gwent_redraw().size() == 0)
                    MessageBox(hwndDlg, "핸드가 꽉 찾습니다.", "ERROR", MB_OK);
                update_ui(hwndDlg);
                break;
            // Mulligan
            case IDC_MUL_1:
                if(gwent_mulligan(0).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_2:
                if(gwent_mulligan(1).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_3:
                if(gwent_mulligan(2).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_4:
                if(gwent_mulligan(3).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_5:
                if(gwent_mulligan(4).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_6:
                if(gwent_mulligan(5).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_7:
                if(gwent_mulligan(6).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_8:
                if(gwent_mulligan(7).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_9:
                if(gwent_mulligan(8).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_MUL_10:
                if(gwent_mulligan(9).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;

            // Delete card from hand
            case IDC_DEL_1:
                if(gwent_hand_to_grave(0).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_2:
                if(gwent_hand_to_grave(1).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_3:
                if(gwent_hand_to_grave(2).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_4:
                if(gwent_hand_to_grave(3).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_5:
                if(gwent_hand_to_grave(4).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_6:
                if(gwent_hand_to_grave(5).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_7:
                if(gwent_hand_to_grave(6).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_8:
                if(gwent_hand_to_grave(7).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_9:
                if(gwent_hand_to_grave(8).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;
            case IDC_DEL_10:
                if(gwent_hand_to_grave(9).size() == 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg);
                break;

            // Card info view
            case IDC_SHOW_CARD_1:
                if(show_card_info(0) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_2:
                if(show_card_info(1) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_3:
                if(show_card_info(2) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_4:
                if(show_card_info(3) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_5:
                if(show_card_info(4) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_6:
                if(show_card_info(5) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_7:
                if(show_card_info(6) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_8:
                if(show_card_info(7) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_9:
                if(show_card_info(8) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_10:
                if(show_card_info(9) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            }
        }
        return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
