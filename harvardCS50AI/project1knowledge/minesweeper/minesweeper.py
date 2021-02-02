import itertools
import random
import copy


class Minesweeper():
    """
    Minesweeper game representation
    """

    def __init__(self, height=8, width=8, mines=8):

        # Set initial width, height, and number of mines
        self.height = height
        self.width = width
        self.mines = set()

        # Initialize an empty field with no mines
        self.board = []
        for i in range(self.height):
            row = []
            for j in range(self.width):
                row.append(False)
            self.board.append(row)

        # Add mines randomly
        while len(self.mines) != mines:
            i = random.randrange(height)
            j = random.randrange(width)
            if not self.board[i][j]:
                self.mines.add((i, j))
                self.board[i][j] = True

        # At first, player has found no mines
        self.mines_found = set()

    def print(self):
        """
        Prints a text-based representation
        of where mines are located.
        """
        for i in range(self.height):
            print("--" * self.width + "-")
            for j in range(self.width):
                if self.board[i][j]:
                    print("|X", end="")
                else:
                    print("| ", end="")
            print("|")
        print("--" * self.width + "-")

    def is_mine(self, cell):
        i, j = cell
        return self.board[i][j]

    def nearby_mines(self, cell):
        """
        Returns the number of mines that are
        within one row and column of a given cell,
        not including the cell itself.
        """

        # Keep count of nearby mines
        count = 0

        # Loop over all cells within one row and column
        for i in range(cell[0] - 1, cell[0] + 2):
            for j in range(cell[1] - 1, cell[1] + 2):

                # Ignore the cell itself
                if (i, j) == cell:
                    continue

                # Update count if cell in bounds and is mine
                if 0 <= i < self.height and 0 <= j < self.width:
                    if self.board[i][j]:
                        count += 1

        return count

    def won(self):
        """
        Checks if all mines have been flagged.
        """
        return self.mines_found == self.mines


class Sentence():
    """
    Logical statement about a Minesweeper game
    A sentence consists of a set of board cells,
    and a count of the number of those cells which are mines.
    """

    def __init__(self, cells, count):
        self.cells = set(cells)
        self.count = count

    def __eq__(self, other):
        return self.cells == other.cells and self.count == other.count

    def __str__(self):
        return f"{self.cells} = {self.count}"

    def known_mines(self):
        """
        Returns the set of all cells in self.cells known to be mines.
        """

        if len(self.cells) == self.count:
            return self.cells
        return set()

    def known_safes(self):
        """
        Returns the set of all cells in self.cells known to be safe.
        """

        if self.count == 0:
            return self.cells
        return set()

    def mark_mine(self, cell):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be a mine.
        """

        if cell in self.cells:
            self.cells.remove(cell)
            self.count = self.count - 1

    def mark_safe(self, cell):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be safe.
        """

        if cell in self.cells:
            self.cells.remove(cell)


class MinesweeperAI():
    """
    Minesweeper game player
    """

    def __init__(self, height=8, width=8):

        # Set initial height and width
        self.height = height
        self.width = width

        # Keep track of which cells have been clicked on
        self.moves_made = set()

        # Keep track of cells known to be safe or mines
        self.mines = set()
        self.safes = set()

        # List of sentences about the game known to be true
        self.knowledge = []

    def mark_mine(self, cell):
        """
        Marks a cell as a mine, and updates all knowledge
        to mark that cell as a mine as well.
        """
        self.mines.add(cell)
        for sentence in self.knowledge:
            sentence.mark_mine(cell)

    def mark_safe(self, cell):
        """
        Marks a cell as safe, and updates all knowledge
        to mark that cell as safe as well.
        """
        self.safes.add(cell)
        for sentence in self.knowledge:
            sentence.mark_safe(cell)

    def add_knowledge(self, cell, count):
        """
        Called when the Minesweeper board tells us, for a given
        safe cell, how many neighboring cells have mines in them.

        This function should:
            1) mark the cell as a move that has been made
            2) mark the cell as safe
            3) add a new sentence to the AI's knowledge base
               based on the value of `cell` and `count`
            4) mark any additional cells as safe or as mines
               if it can be concluded based on the AI's knowledge base
            5) add any new sentences to the AI's knowledge base
               if they can be inferred from existing knowledge
        """
        # 1) mark the cell as a move that has been made
        self.moves_made.add(cell)

        # 2) mark the cell as safe which will remove this cell from all sentences in knowledge
        self.mark_safe(cell)

        # 3) construct new sentence based on neighboring cells minus known mines/safes (states undetermined)
        neighbor_set = set()

        for i in range(cell[0] - 1, cell[0] + 2):
            for j in range(cell[1] - 1, cell[1] + 2):

                # Ignore the cell itself
                if (i, j) == cell:
                    continue

                # Update count if cell in bounds
                if 0 <= i < self.height and 0 <= j < self.width:
                    neighbor_set.add((i, j))

        # Only get neighbors that is unrevealed
        neighbor_set = neighbor_set - self.moves_made
        # Make sure to not include any known mines and remove count if found (only mine affects counts)
        mine_count = 0
        for cell in neighbor_set:
            if cell in self.mines:
                mine_count = mine_count + 1
        # Add new sentence to knowledge base
        self.knowledge.append(Sentence(neighbor_set - self.mines - self.safes, count - mine_count))

        while True:
            initial_knowledge = copy.deepcopy(self.knowledge)
            # Keep making inferences on current move on original self.knowledge
            self.recursive_inference()

            # No changes to self.knowledge means that recursive_inference could not make any more inferences
            if initial_knowledge == self.knowledge:
                break


    def recursive_inference(self):
        # 4
        # Mark any additional cells as safe or as mines

        # Go through each sentence in knowledge and remove known minescells (update mine_count) and remove known safecells
        knowledge_copy = copy.deepcopy(self.knowledge)  # will break if self.knowledge is modified during iteration
        for sentence in knowledge_copy:
            if len(sentence.known_mines()) > 0:
                for mine_cells in sentence.known_mines():
                    self.mark_mine(mine_cells)
            if len(sentence.known_safes()) > 0:
                for safe_cells in sentence.known_safes():
                    self.mark_safe(safe_cells)

        # 5)
        # add any new sentences to the AI's knowledge base, if they can be inferred from existing knowledge

        # Iterate through each sentence in a knowledge, check other sentences in knowledge if its a subset
        knowledge_copy = copy.deepcopy(self.knowledge)  # will break if self.knowledge is modified during iteration
        for sentence in knowledge_copy:
            for sub_sentence in knowledge_copy:
                # Dont compare the same sentence in knowledge and check if other sentences are subsets of each other
                if sub_sentence.cells.issubset(sentence.cells) and sentence.cells != sub_sentence.cells:
                    # Check if subset is an empty set  (it will pass the above two conditions)
                    if len(sub_sentence.cells) != 0:  # Empty sets have length of 0
                        self.knowledge.append(
                            Sentence(sentence.cells - sub_sentence.cells, sentence.count - sub_sentence.count)
                        )

        # Clean up self.knowledge for any empty sets
        knowledge_cleanup = []
        for sentence in self.knowledge:
            if len(sentence.cells) != 0 and sentence not in knowledge_cleanup:  # Empty sets have length of 0
                knowledge_cleanup.append(sentence)
        self.knowledge = knowledge_cleanup

    def make_safe_move(self):
        """
        Returns a safe cell to choose on the Minesweeper board.
        The move must be known to be safe, and not already a move
        that has been made.

        This function may use the knowledge in self.mines, self.safes
        and self.moves_made, but should not modify any of those values.

        iterate through all self.safes known, if it is not in moves_made, return that cell?

        """
        print(self.safes - self.moves_made)
        for safecell in self.safes:
            if safecell not in self.moves_made:
                return safecell
        return None

    def make_random_move(self):
        """
        Returns a move to make on the Minesweeper board.
        Should choose randomly among cells that:
            1) have not already been chosen, and
            2) are not known to be mines

        make a board
        remove all cells mines and already made
        if board set length == 0 Return none
        Else select a cell in board

        """
        boardset = set()
        for i in range(8):
            for j in range(8):
                boardset.add((i,j))

        boardset = boardset - self.moves_made - self.mines
        if len(boardset) == 0:
            return None
        return random.sample(boardset, 1)[0]

