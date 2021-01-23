"""
Tic Tac Toe Player
"""

import math
from copy import deepcopy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    numx = 0
    numo = 0

    # Find out the number of X or Os on the current board
    for row in board:
        for col in row:
            if col == X:
                numx += 1
            elif col == O:
                numo += 1

    # Since X always goes first, if there is equal number of each player, X will go next
    if numx == numo:
        return X
    else:
        return O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    actionset = set()

    # Iterate through the whole board to check for empty spaces and add the location to the actionset
    for row in range(3):
        for col in range(3):
            if board[row][col] is EMPTY:
                actionset.add((row, col))
    return actionset


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    # Create a deep copy of the board
    copyBoard = deepcopy(board)

    # Check to make sure it is a valid action on an empty space before taking action
    actionRow = action[0]
    actionCol = action[1]
    if copyBoard[actionRow][actionCol] is not EMPTY:
        raise Exception
    else:
        copyBoard[actionRow][actionCol] = player(copyBoard)

    # return new board with the action implemented
    return copyBoard


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """

    winCombos = [[(0, 0), (0, 1), (0, 2)], [(1, 0), (1, 1), (1, 2)], [(2, 0), (2, 1), (2, 2)],  # Row winners
                [(0, 0), (1, 0), (2, 0)], [(0, 1), (1, 1), (2, 1)], [(0, 2), (1, 2), (2, 2)],  # Column winners
                [(0, 0), (1, 1), (2, 2)], [(2, 0), (1, 1), (0, 2)]]  # Diagonal Winners

    # iterate through each possible sets of a way a player can win
    for winCombo in winCombos:
        numX, numO = 0, 0  # Initialize Count of X and O

        # Search through each Location in the winner set
        for cell in winCombo:
            # Search through current board location for number of X or O in winner set
            if board[cell[0]][cell[1]] == X:
                numX += 1
            elif board[cell[0]][cell[1]] == O:
                numO += 1

        # If Player (X or O) has 3 in all locations of the set, that is the winning player
        if numX == 3:
            return X
        elif numO == 3:
            return O

    # If no player won 3 in a row in all winner combinations, no winner exists
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.

    1. Check if Winner return X or O (Return true)
    2. ELSE: Check if Winner returns NONE
            - Check Board is fulled (return true)
            - else: Return False
    """
    # Game Ends when there is a winner (X or O wins)
    if winner(board) == X or winner(board) == O:
        return True
    else:
        # Search through board to see if any more empty spaces
        for row in range(3):
            for col in range(3):
                # If an empty space is seen, then Game still continues (return false)
                if board[row][col] is EMPTY:
                    return False
        # Game has ended if no empty spaces
        return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """

    # Created a dictionary of utility values based on winner
    utility_dict = {
        X: 1,
        O: -1
    }

    return utility_dict.get(winner(board), 0)  # Return 0 if not in dictionary


def minvalue(board):
    # initialize values for min value (lowest) and action associated with that min value
    minv = math.inf
    minaction = None

    # return the utility (-1. 0, 1) of the board if terminal
    if terminal(board):
        return utility(board), minaction

    # Use recursion to find the min value then update the action associated with that value
    for action in actions(board):
        tempmin, _ = maxvalue(result(board, action)) # Previous action does not matter (_ is a throwaway variable)
        if tempmin < minv:
            minv = tempmin
            minaction = action

    # Return value to be used in recursion and best action
    return minv, minaction


def maxvalue(board):
    # initialize values for max value (greatest) and action associated with that max value
    maxv = -math.inf
    maxaction = None

    # return the utility (-1. 0, 1) of the board if terminal
    if terminal(board):
        return utility(board), maxaction

    # Use recursion to find the max value then update the action associated with that value
    for action in actions(board):
        tempmax, _ = minvalue(result(board, action))  # Previous action does not matter (_ is a throwaway variable)
        if tempmax > maxv:
            maxv = tempmax
            maxaction = action

    # Return value to be used in recursion and best action
    return maxv, maxaction


def minimax(board):
    """
    Returns the optimal action for the current player on the board.

    1. Determine the next player on the board
    2. Call maxvalue on X player, Call minvalue on O player
    3. maxvalue and minvalue should return a action or none if no action.
    """
    # if the board is a terminal board, the min-max function should return None
    if terminal(board):
        return None

    if player(board) == X:
        # if the player is X, it will try to get the max value (_ is a throwaway variable)
        _, bestaction = maxvalue(board)
    else:
        # if the player is O, it will try to get the min value
        _, bestaction = minvalue(board)

    return bestaction


