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

void update_ui(HWND hwnd, GWENT_TYPE * deck, GWENT_TYPE * hand)
{
    // clear card name
    for (int i = 0; i < 10; i++)
        SetDlgItemText(hwnd, card_names[i], "");

    for(int i = 0; i < hand->size(); i++)
    {
        char * card_str = new char[hand->at(i).length()];
        char * p;
        memcpy(card_str, hand->at(i).c_str(), hand->at(i).length());
        p = strtok(card_str, "@");
        SetDlgItemText(hwnd, card_names[i], p);
        delete card_str;
    }
    SetDlgItemInt(hwnd, IDC_CARD_COUNT, deck->size(), 0);
}

void get_card_img_url(GWENT_TYPE * hand, int index, char * url)
{
        char * p;
        char card_str[MAX_PATH];
        sprintf(card_str, "%s", hand->at(index).c_str());
        printf("%s",  card_str);
        p = strtok(card_str, "@");
        p = strtok(NULL, "@");
        memcpy(url, p, strlen(p));
        url[strlen(url)] = '\0';
}

int show_card_info(GWENT_TYPE hand, int card_no)
{
    char card_url[MAX_PATH] = {0, };

    if(hand.size() == 0)
        return -1;

    if(card_no > hand.size())
        return -1;

    memset(card_url, 0, MAX_PATH);
    get_card_img_url(&hand, card_no, card_url);
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
                memset(deck_path, 0, MAX_PATH);
                open_deck(hwndDlg, deck_path);
                deck.clear();
                hand.clear();
                loaddeck(deck_path, &deck);
                draw(&deck, &hand, 10);
                update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_REPLAY:
                deck.clear();
                hand.clear();
                loaddeck(deck_path, &deck);
                draw(&deck, &hand, 10);
                update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_RESHUFFLE:
                shuffle_deck(&deck, deck.size());
                break;
            case IDC_DRAW:
                if(redraw(&deck, &hand) < 0)
                    MessageBox(hwndDlg, "핸드가 꽉 찾습니다.", "ERROR", MB_OK);
                update_ui(hwndDlg, &deck, &hand);
                break;
            // Mulligan
            case IDC_MUL_1:
                if(mulligan(&deck, &hand, 0) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_2:
                if(mulligan(&deck, &hand, 1) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_3:
                if(mulligan(&deck, &hand, 2) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_4:
                if(mulligan(&deck, &hand, 3) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_5:
                if(mulligan(&deck, &hand, 4) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_6:
                if(mulligan(&deck, &hand, 5) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_7:
                if(mulligan(&deck, &hand, 6) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_8:
                if(mulligan(&deck, &hand, 7) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_9:
                if(mulligan(&deck, &hand, 8) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_MUL_10:
                if(mulligan(&deck, &hand, 9) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;

            // Delete card from hand
            case IDC_DEL_1:
                if(remove_card(&hand, 0) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_2:
                if(remove_card(&hand, 1) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_3:
                if(remove_card(&hand, 2) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_4:
                if(remove_card(&hand, 3) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_5:
                if(remove_card(&hand, 4) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_6:
                if(remove_card(&hand, 5) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_7:
                if(remove_card(&hand, 6) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_8:
                if(remove_card(&hand, 7) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_9:
                if(remove_card(&hand, 8) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;
            case IDC_DEL_10:
                if(remove_card(&hand, 9) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                else
                    update_ui(hwndDlg, &deck, &hand);
                break;

            // Card info view
            case IDC_SHOW_CARD_1:
                if( show_card_info(hand, 0) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_2:
                if( show_card_info(hand, 1) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_3:
                if( show_card_info(hand, 2) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_4:
                if( show_card_info(hand, 3) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_5:
                if( show_card_info(hand, 4) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_6:
                if( show_card_info(hand, 5) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_7:
                if( show_card_info(hand, 6) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_8:
                if( show_card_info(hand, 7) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_9:
                if( show_card_info(hand, 8) < 0)
                    MessageBox(hwndDlg, "없는 카드 입니다.", "ERROR", MB_OK);
                break;
            case IDC_SHOW_CARD_10:
                if( show_card_info(hand, 9) < 0)
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
