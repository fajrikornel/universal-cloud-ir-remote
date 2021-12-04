void record_loop();
void schedule_loop(int);
int empty_schedule();

void messageReceivedAdvanced(MQTTClient *client, char topic[], char bytes[], int length)
{
  if ((length > 0) && (topic[29] == 'm')) {
    if ((unsigned char) bytes[0] == 0xFF) {
      //request transmit
      Serial.println("Requesting transmit");
      Serial.flush();
      unsigned char parse_bytes[13];
      for (int i = 0; i < 13; i++) {
        parse_bytes[i] = (unsigned char) bytes[i];
      }

      int time = (bytes[1] << 24) | (bytes[2] << 16) | (bytes[3] << 8) | (bytes[4]);
      IRData send_code;
      send_code.protocol = (decode_type_t) ((parse_bytes[5] << 24) | (parse_bytes[6] << 16) | (parse_bytes[7] << 8) | (parse_bytes[8]));
      send_code.address = (uint16_t) ((parse_bytes[9] << 8) | (parse_bytes[10]));
      send_code.command = (uint16_t) ((parse_bytes[11] << 8) | (parse_bytes[12]));
      send_code.flags = IRDATA_FLAGS_EMPTY;

      if (time == 0) {
        IrReceiver.stop();
        delay(100);
        IrSender.write(&send_code, NO_REPEATS);
        delay(100);
        IrReceiver.resume();
      } else if (time > 0) {
        int schedule_cursor = empty_schedule();
        Serial.printf("Transmit is scheduled at number: %d\n",schedule_cursor);
        if (schedule_cursor != -1) {
          timeout_schedule[schedule_cursor] = time;
          last_schedule[schedule_cursor] = millis();
          schedule_code[schedule_cursor] = send_code;
          schedule_status[schedule_cursor] = true;
        } else {
          Serial.println("Cannot schedule!!! Maximum three scheduled activity");
        }
      }
    } else if ((unsigned char) bytes[0] == 0xFE) {
      //request record
      Serial.printf("Requesting record of %c%c%c%c%c%c%c%c%c\n",bytes[1],bytes[2],bytes[3],bytes[4],bytes[5],bytes[6],bytes[7],bytes[8]);
      for (int i = 0; i < 16; i++) {
        buf_send[i] = 0x0;
      }
      digitalWrite(LED_RECEIVE, HIGH);
      for (int i = 1; i < length; i++) {
        buf_send[i + 7] =  bytes[i];
      }
      lastRecord = millis();
      recording = true;
    } else {
      //invalid request
      printf("haha");
    }
  } else {
    //Serial.printf("0\n"); // Success but no message
  }
}

void record_loop() {
  if ((millis() - lastRecord > 5000) && recording)
  {
    if (IrReceiver.available()) {
      IRData * rec_data = IrReceiver.read();
      if (rec_data->protocol != UNKNOWN) {
        Serial.println("Data recorded.");
        buf_send[0] = (rec_data->protocol >> 24) & 0xFF;
        buf_send[1] = (rec_data->protocol >> 16) & 0xFF;
        buf_send[2] = (rec_data->protocol >> 8) & 0xFF;
        buf_send[3] = (rec_data->protocol) & 0xFF;
        buf_send[4] = (rec_data->address >> 8) & 0xFF;
        buf_send[5] = (rec_data->address) & 0xFF;
        buf_send[6] = (rec_data->command >> 8) & 0xFF;
        buf_send[7] = (rec_data->command) & 0xFF;
        IrReceiver.printIRResultShort(&Serial);
        Serial.flush();
        publishTelemetry(buf_send, 16);
      }
      IrReceiver.resume();
    }
    digitalWrite(LED_RECEIVE, LOW);
    recording = false;
  }
}

void schedule_loop(int schedule_number) {
  if ((millis() - last_schedule[schedule_number] > timeout_schedule[schedule_number]) && schedule_status[schedule_number])
  {
    Serial.printf("Executing schedule number %d\n",schedule_number);
    Serial.flush();
    IrReceiver.stop();
    delay(100);
    IrSender.write(&schedule_code[schedule_number], NO_REPEATS);
    delay(100);
    IrReceiver.resume();
    schedule_status[schedule_number] = false;
  }
}

int empty_schedule() {
  for (int i = 0; i < 3; i++) {
    if (!schedule_status[i]) {
      return i;
    }
  }
  return -1;
}
