#include <pebble.h>
#include "track.h"
#include "items.h"

static void received_handler(DictionaryIterator *iter, void *context) {
  update_ifttt(iter);
  update_items(iter);
  update_todoist(iter);
}

void store_string(DictionaryIterator *iter, uint32_t key) {
  Tuple *tuple = dict_find(iter, key);
  if (tuple) {
    persist_write_string(key, tuple->value->cstring);
  }
}

int read_string(uint32_t key, char* buffer, int buffer_size) {
  int written = persist_read_string(key, buffer, buffer_size);
  if (written >= buffer_size * (int)sizeof(char))
    buffer[buffer_size - 1] = '\0';
  return written;
}

void init_app_message() {
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  app_message_register_inbox_received(received_handler);
}