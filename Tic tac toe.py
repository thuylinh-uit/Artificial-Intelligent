from tkinter import *
from tkinter import messagebox
import operator

root = Tk()
root.title("Tic Tac Toe")

click = True
player = [' ', 'X', 'O']
case_win = [1, 2, 3, 4, 5, 6, 7, 8]
case_win_oxy = {(0, 0): [1, 4, 7],
            (0, 1): [1, 5],
            (0, 2): [1, 6, 8],
            (1, 0): [2, 4],
            (1, 1): [2, 5, 7, 8],
            (1, 2): [2, 6],
            (2, 0): [3, 4, 8],
            (2, 1): [3, 5],
            (2, 2): [3, 6, 7]}

def isFull(board):
    for i in range(0, 3):
        if board[i][0]["text"] == player[0] or board[i][1]["text"] == player[0] or board[i][2]["text"] == player[0]:
            return False
    return True

def Check_Human_Win(player, board):
    for i in range(0, 3):
        if board[i][0]["text"] == player[1] and board[i][1]["text"] == player[1] and board[i][2]["text"] == player[1]:
            return True
        if board[0][i]["text"] == player[1] and board[1][i]["text"] == player[1] and board[2][i]["text"] == player[1]:
            return True
    if board[0][0]["text"] == player[1] and board[1][1]["text"] == player[1] and board[2][2]["text"] == player[1]:
        return True
    if board[0][2]["text"] == player[1] and board[1][1]["text"] == player[1] and board[2][0]["text"] == player[1]:
        return True
    return False

def Check_Bot_Win(player, board):
    for i in range(0, 3):
        if (board[i][0]["text"] == player[2] and board[i][1]["text"] == player[2] and board[i][2]["text"] == player[2])\
        or (board[0][i]["text"] == player[2] and board[1][i]["text"] == player[2] and board[2][i]["text"] == player[2]):
            return True
    if board[0][0]["text"] == player[2] and board[1][1]["text"] == player[2] and board[2][2]["text"] == player[2]:
        return True
    if board[0][2]["text"] == player[2] and board[1][1]["text"] == player[2] and board[2][0]["text"] == player[2]:
        return True
    return False

def Win_Case_Human(buttons, player):
    case_bot = []
    for i in range(0, 3):
        for j in range(0, 3):
            if buttons[i][j]["text"] == player[2]:
                for case in case_win_oxy[(i, j)]:
                    if case not in case_bot:
                        case_bot.append(case)
    result = [i for i in case_win if not i in case_bot]
    return len(result)

def Win_Case_Bot(buttons, player):
    case_human = []
    for i in range(0, 3):
        for j in range(0, 3):
            if buttons[i][j]["text"] == player[1]:
                for case in case_win_oxy[(i, j)]:
                    if case not in case_human:
                        case_human.append(case)
    result = [i for i in case_win if not i in case_human]
    return len(result)

def Select_Button(buttons, player):
    case = {}
    human_win = []
    flag = False
    for i in range(0, 3):
        for j in range(0, 3):
            if buttons[i][j]["text"] == player[0]:
                buttons[i][j]["text"] = player[2]
                if Check_Bot_Win(player, buttons) == True:
                    return i,j

                buttons[i][j]["text"] = player[1]
                if Check_Human_Win(player, buttons) == True:
                    human_win.append(i)
                    human_win.append(j)
                    flag = True

                buttons[i][j]["text"] = player[2]
                case[(i, j)] = Win_Case_Human(buttons, player)-Win_Case_Bot(buttons, player)
                buttons[i][j]["text"] = player[0]
    if flag == True:
        return human_win[0],human_win[1]

    sorted_case = sorted(case.items(), key=operator.itemgetter(1))
    return sorted_case[0][0][0], sorted_case[0][0][1]

def GameSetting(button, buttons):
    global click

    if click == True:
        if button["text"] == " " and click == True:
            button["text"] = "X"
            if isFull(buttons) == True:
                messagebox.showinfo("Gameover","Draw!")
                root.destroy()
                return
            click = False

            i, j = Select_Button(buttons, player)
            buttons[i][j]["text"] = "O"
            if Check_Bot_Win(player, buttons) == True:
                messagebox.showinfo("Gameover", "Bot win - O")
                root.destroy()
                return
            click = True

buttons = []

button1 = Button(root, text=' ', font=('cambria',16), bg='white', fg='black', height=4, width=9, command=lambda: GameSetting(button1, buttons))
button1.grid(row=1, column=0, sticky=S + N + E + W)
button2 = Button(root, text=' ', font=('cambria',16), bg='pink', fg='black', height=4, width=9, command=lambda: GameSetting(button2, buttons))
button2.grid(row=1, column=1, sticky=S + N + E + W)
button3 = Button(root, text=' ', font=('cambria',16), bg='red', fg='black', height=4, width=9, command=lambda: GameSetting(button3, buttons))
button3.grid(row=1, column=2, sticky=S + N + E + W)

ROW = [button1, button2, button3]
buttons.append(ROW)

button4 = Button(root, text=' ', font=('cambria',16), bg='orange', fg='black', height=4, width=9, command=lambda: GameSetting(button4, buttons))
button4.grid(row=2, column=0, sticky=S + N + E + W)
button5 = Button(root, text=' ', font=('cambria',16), bg='yellow', fg='black', height=4, width=9, command=lambda: GameSetting(button5, buttons))
button5.grid(row=2, column=1, sticky=S + N + E + W)
button6 = Button(root, text=' ', font=('cambria',16), bg='blue', fg='black', height=4, width=9, command=lambda: GameSetting(button6, buttons))
button6.grid(row=2, column=2, sticky=S + N + E + W)

ROW = [button4, button5, button6]
buttons.append(ROW)

button7 = Button(root, text=' ', font=('cambria',16), bg='green', fg='black', height=4, width=9, command=lambda: GameSetting(button7, buttons))
button7.grid(row=3, column=0, sticky=S + N + E + W)
button8 = Button(root, text=' ', font=('cambria',16), bg='purple', fg='black', height=4, width=9, command=lambda: GameSetting(button8, buttons))
button8.grid(row=3, column=1, sticky=S + N + E + W)
button9 = Button(root, text=' ', font=('cambria',16), bg='violet', fg='black', height=4, width=9, command=lambda: GameSetting(button9, buttons))
button9.grid(row=3, column=2, sticky=S + N + E + W)

ROW = [button7, button8, button9]
buttons.append(ROW)

root.mainloop()
