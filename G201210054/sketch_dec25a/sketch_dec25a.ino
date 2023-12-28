// Gaz sensörlerinin bağlı olduğu pinler
const int MQ7_AOUT_PIN = A1;
const int MQ135_AOUT_PIN = A0;
const int BUZZER_PIN = 2;

// Gaz sensörlerinden okunan değerlerin saklanacağı değişkenler
int mq7Value = 0;
int mq135Value = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // MQ7 sensöründen veri okuma
  mq7Value = analogRead(MQ7_AOUT_PIN);
  // MQ135 sensöründen veri okuma
  mq135Value = analogRead(MQ135_AOUT_PIN);

  // Okunan değerleri Serial Monitör'e yazdırma
  Serial.print("MQ7 Değer: ");
  Serial.print(mq7Value);
  Serial.print("\t MQ135 Değer: ");
  Serial.println(mq135Value);

  // Gaz seviyesi eşik değerini kontrol ederek buzzer'ı çalma
  if (mq7Value > 500 || mq135Value > 500) {
    digitalWrite(BUZZER_PIN, HIGH); // Buzzer'ı aktif et
     delay(1000);
      digitalWrite(BUZZER_PIN, LOW); 
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Buzzer'ı kapat
  }

  delay(1000); // 1 saniye bekleme
}
