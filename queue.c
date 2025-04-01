#include "queue.h"
#include "linked_list.h"
#include "tile_game.h"
#include <stdbool.h>
#include <stdio.h>

#define BOARD_SIZE 4

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
  size_t init = remove_from_head(&(q->data));

  return deserialize(init);
}

bool is_finished(struct game_state board) {
  if (board.tiles[3][3] != 0) {
    return false;
  }

  int expected = 1;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (i == 3 && j == 3) {
        continue;
      }

      if (board.tiles[i][j] != expected++) {
        return false;
      }
    }
  }

  return true;
}

int number_of_moves(struct game_state start) {
  struct queue q = {.data = {.head = NULL}};
  enqueue(&q, start);

  while (q.data.head != NULL) {
    struct game_state cur_state = dequeue(&q);
    if (is_finished(cur_state)) {
      free_list(q.data);
      return cur_state.num_steps;
    }

    if (cur_state.empty_row != 0) {
      struct game_state new_state = cur_state;
      move_down(&new_state);
      enqueue(&q, new_state);
    }

    if (cur_state.empty_row != BOARD_SIZE - 1) {
      struct game_state new_state = cur_state;
      move_up(&new_state);
      enqueue(&q, new_state);
    }

    if (cur_state.empty_col != 0) {
      struct game_state new_state = cur_state;
      move_right(&new_state);
      enqueue(&q, new_state);
    }

    if (cur_state.empty_col != BOARD_SIZE - 1) {
      struct game_state new_state = cur_state;
      move_left(&new_state);
      enqueue(&q, new_state);
    }
  }

  free_list(q.data);
  return -1;
}
