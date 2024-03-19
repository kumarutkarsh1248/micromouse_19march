#include "flood_fill.h"

SimpleStack<Cell> cellStack(300);
Cell cell1;

void flood_fill() {
  while (!cellStack.isEmpty()) {
    Cell working_cell;
    cellStack.pop(&working_cell);
    int i = working_cell.i;
    int j = working_cell.j;

    if (working_cell.config == all_blocked) {
      continue;
    } else if (working_cell.config == all_clear) {
      maze[i][j].visited = true;
      right_flood_fill(i, j);
      back_flood_fill(i, j);
      left_flood_fill(i, j);
      front_flood_fill(i, j);
    }

    else if (working_cell.config == right_back_left_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
    } else if (working_cell.config == front_right_back_blocked) {
      maze[i][j].visited = true;
      left_flood_fill(i, j);
    } else if (working_cell.config == front_back_left_blocked) {
      maze[i][j].visited = true;
      right_flood_fill(i, j);
    } else if (working_cell.config == front_right_left_blocked) {
      maze[i][j].visited = true;
      back_flood_fill(i, j);
    }

    else if (working_cell.config == back_left_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
      right_flood_fill(i, j);
    } else if (working_cell.config == right_back_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
      left_flood_fill(i, j);
    } else if (working_cell.config == front_right_blocked) {
      maze[i][j].visited = true;
      left_flood_fill(i, j);
      back_flood_fill(i, j);
    } else if (working_cell.config == front_left_blocked) {
      maze[i][j].visited = true;
      right_flood_fill(i, j);
      back_flood_fill(i, j);
    } else if (working_cell.config == front_back_blocked) {
      maze[i][j].visited = true;
      left_flood_fill(i, j);
      right_flood_fill(i, j);
    } else if (working_cell.config == right_left_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
      back_flood_fill(i, j);
    }

    else if (working_cell.config == right_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
      back_flood_fill(i, j);
      left_flood_fill(i, j);
    } else if (working_cell.config == left_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
      back_flood_fill(i, j);
      right_flood_fill(i, j);
    } else if (working_cell.config == front_blocked) {
      maze[i][j].visited = true;
      right_flood_fill(i, j);
      back_flood_fill(i, j);
      left_flood_fill(i, j);
    } else if (working_cell.config == back_blocked) {
      maze[i][j].visited = true;
      front_flood_fill(i, j);
      right_flood_fill(i, j);
      left_flood_fill(i, j);
    }
  }
}



void right_flood_fill(int i, int j) {
  if (i > SIZE - 1) {
    return;
  }
  if (maze[i + 1][j].visited == true && maze[i + 1][j].distance <= maze[i][j].distance + 1) {
    return;
  }
  maze[i + 1][j].distance = maze[i][j].distance + 1;
  cellStack.push(maze[i + 1][j]);
}
void back_flood_fill(int i, int j) {
  if (j < 0) {
    return;
  }
  if (maze[i][j - 1].visited == true && maze[i][j - 1].distance <= maze[i][j].distance + 1) {
    return;
  }
  maze[i][j - 1].distance = maze[i][j].distance + 1;
  cellStack.push(maze[i][j - 1]);
}
void left_flood_fill(int i, int j) {
  if (i < 0) {
    return;
  }
  if (maze[i - 1][j].visited == true && maze[i - 1][j].distance <= maze[i][j].distance + 1) {
    return;
  }
  maze[i - 1][j].distance = maze[i][j].distance + 1;
  cellStack.push(maze[i - 1][j]);
}
void front_flood_fill(int i, int j) {
  if (j > SIZE - 1) {
    return;
  }
  if (maze[i][j + 1].visited == true && maze[i][j + 1].distance <= maze[i][j].distance + 1) {
    return;
  }
  maze[i][j + 1].distance = maze[i][j].distance + 1;
  cellStack.push(maze[i][j + 1]);
}



Cell::Cell() {
  i = 1;
  j = 0;
};
Cell::Cell(uint8_t i, uint8_t j) {
  this->i = i;
  this->j = j;
};
void Cell::update() {
  if (right_wall == true && left_wall == true && front_wall == true && back_wall == true) {
    config = all_blocked;
  } else if (right_wall == false && left_wall == false && front_wall == false && back_wall == false) {
    config = all_clear;
  }

  else if (right_wall == true && left_wall == false && front_wall == false && back_wall == false) {
    config = right_blocked;
  } else if (right_wall == false && left_wall == true && front_wall == false && back_wall == false) {
    config = left_blocked;
  } else if (right_wall == false && left_wall == false && front_wall == true && back_wall == false) {
    config = front_blocked;
  } else if (right_wall == false && left_wall == false && front_wall == false && back_wall == true) {
    config = back_blocked;
  }

  else if (right_wall == true && left_wall == true && front_wall == false && back_wall == false) {
    config = right_left_blocked;
  } else if (right_wall == false && left_wall == false && front_wall == true && back_wall == true) {
    config = front_back_blocked;
  } else if (right_wall == true && left_wall == false && front_wall == false && back_wall == true) {
    config = right_back_blocked;
  } else if (right_wall == false && left_wall == true && front_wall == true && back_wall == false) {
    config = front_left_blocked;
  } else if (right_wall == false && left_wall == true && front_wall == false && back_wall == true) {
    config = back_left_blocked;
  } else if (right_wall == true && left_wall == false && front_wall == true && back_wall == false) {
    config = front_right_blocked;
  }

  else if (right_wall == false && left_wall == true && front_wall == true && back_wall == true) {
    config = front_back_left_blocked;
  } else if (right_wall == true && left_wall == false && front_wall == true && back_wall == true) {
    config = front_right_back_blocked;
  } else if (right_wall == true && left_wall == true && front_wall == false && back_wall == true) {
    config = right_back_left_blocked;
  } else if (right_wall == true && left_wall == true && front_wall == true && back_wall == false) {
    config = front_right_left_blocked;
  }
}

void set_boundary_wall() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      maze[i][j] = Cell(i, j);
      maze[i][j].left_wall = false;
      maze[i][j].right_wall = false;
      maze[i][j].front_wall = false;
      maze[i][j].back_wall = false;
      if (i == 0) {
        maze[i][j].left_wall = true;
      }
      if (i == SIZE - 1) {
        maze[i][j].right_wall = true;
      }
      if (j == 0) {
        maze[i][j].back_wall = true;
      }
      if (j == SIZE - 1) {
        maze[i][j].front_wall = true;
      }
      maze[i][j].update();
    }
  }
  whole_flood_fill();
}

void bot_update_wall() {
  if (bot.orientation == bot_front) {
    if (distance.front_wall) {
      found_wall(bot.x, bot.y, "front");
    }
    if (distance.right_wall) {
      found_wall(bot.x, bot.y, "right");
    }
    if (distance.left_wall) {
      found_wall(bot.x, bot.y, "left");
    }
  }

  else if (bot.orientation == bot_right) {
    if (distance.front_wall) {
      found_wall(bot.x, bot.y, "right");
    }
    if (distance.right_wall) {
      found_wall(bot.x, bot.y, "back");
    }
    if (distance.left_wall) {
      found_wall(bot.x, bot.y, "front");
    }
  }
  if (bot.orientation == bot_left) {
    if (distance.front_wall) {
      found_wall(bot.x, bot.y, "left");
    }
    if (distance.right_wall) {
      found_wall(bot.x, bot.y, "front");
    }
    if (distance.left_wall) {
      found_wall(bot.x, bot.y, "back");
    }
  }
  if (bot.orientation == bot_back) {
    if (distance.front_wall) {
      found_wall(bot.x, bot.y, "back");
    }
    if (distance.right_wall) {
      found_wall(bot.x, bot.y, "left");
    }
    if (distance.left_wall) {
      found_wall(bot.x, bot.y, "right");
    }
  }
}


int where_to_move(int i, int j) {
  SimpleStack<Cell> neighbor(4);
  // Check each direction for neighbors
  if (i > 0) {
    neighbor.push(maze[i - 1][j]);  // Upper neighbor
  }
  if (i < SIZE - 1) {
    neighbor.push(maze[i + 1][j]);  // Lower neighbor
  }
  if (j > 0) {
    neighbor.push(maze[i][j - 1]);  // Left neighbor
  }
  if (j < SIZE - 1) {
    neighbor.push(maze[i][j + 1]);  // Right neighbor
  }

  SimpleStack<Cell> less_dist_neighbor(4);
  while (!neighbor.isEmpty()) {
    Cell trial_neighbor;
    neighbor.pop(&trial_neighbor);
    if (trial_neighbor.distance <= maze[i][j].distance && possible_or_not(maze[i][j], trial_neighbor)) {
      less_dist_neighbor.push(trial_neighbor);
    }
  }

  Cell min_dist_neighbor;
  less_dist_neighbor.pop(&min_dist_neighbor);
  while (!less_dist_neighbor.isEmpty()) {
    Cell trial_neighbor;
    less_dist_neighbor.pop(&trial_neighbor);
    if (trial_neighbor.distance <= min_dist_neighbor.distance) {
      min_dist_neighbor = trial_neighbor;
    }
  }
  // setColor(min_dist_neighbor.i, min_dist_neighbor.j, 'R');

  int dx = min_dist_neighbor.i - bot.x;
  int dy = min_dist_neighbor.j - bot.y;

  if (dx == 1 && dy == 0) {
    return cell_right;
  } else if (dx == 0 && dy == -1) {
    return cell_back;
  } else if (dx == 0 && dy == 1) {
    return cell_front;
  } else if (dx == -1 && dy == 0) {
    return cell_left;
  }
  return 0;
}


bool possible_or_not(Cell initial_cell, Cell final_cell) {
  if (initial_cell.i == final_cell.i - 1) {
    if (!initial_cell.right_wall && !final_cell.left_wall) {
      return true;
    } else {
      return false;
    }
  } else if (initial_cell.i == final_cell.i + 1) {
    if (!initial_cell.left_wall && !final_cell.right_wall) {
      return true;
    } else {
      return false;
    }
  } else if (initial_cell.j == final_cell.j - 1) {
    if (!initial_cell.front_wall && !final_cell.back_wall) {
      return true;
    } else {
      return false;
    }
  } else if (initial_cell.j == final_cell.j + 1) {
    if (!initial_cell.back_wall && !final_cell.front_wall) {
      return true;
    } else {
      return false;
    }
  }
  return true;
}


void found_wall(int i, int j, String wall) {
  if ((i == 0 && wall == "left") || (i == SIZE - 1 && wall == "right") || (j == SIZE - 1 && wall == "front") || (j == 0 && wall == "back")) {
    return;
  }
  if (wall == "right") {
    maze[i][j].right_wall = true;
    maze[i + 1][j].left_wall = true;
    maze[i][j].update();
    maze[i + 1][j].update();
  } else if (wall == "left") {
    maze[i][j].left_wall = true;
    maze[i - 1][j].right_wall = true;
    maze[i][j].update();
    maze[i - 1][j].update();
  } else if (wall == "front") {
    maze[i][j].front_wall = true;
    maze[i][j + 1].back_wall = true;
    maze[i][j].update();
    maze[i][j + 1].update();
  } else if (wall == "back") {
    maze[i][j].back_wall = true;
    maze[i][j - 1].front_wall = true;
    maze[i][j].update();
    maze[i][j - 1].update();
  }
}



int z = 0;
void whole_flood_fill() {
  z++;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      maze[i][j].distance = 0;
      maze[i][j].visited = false;
    }
  }
  maze[7][7].visited = true;
  maze[8][8].visited = true;
  maze[8][7].visited = true;
  maze[7][8].visited = true;

  cellStack.push(maze[7][7]);
  cellStack.push(maze[7][8]);
  cellStack.push(maze[8][7]);
  cellStack.push(maze[8][8]);
  flood_fill();

  // if (z == 12) {
  //   for (int i = 0; i < SIZE; i++) {
  //     for (int j = 0; j < SIZE; j++) {
  //       setText(i, j, String(maze[i][j].distance));
  //     }
  //   }
  // }
}