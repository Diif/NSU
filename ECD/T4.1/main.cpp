#include <libusb-1.0/libusb.h>
#include <stdio.h>

#include <iostream>
#define TITLE1_LEN 6
#define TITLE3_LEN 7
#define TITLE2_LEN 10
#define TITLE3_LEN 15
#define TITLE4_LEN 50

using namespace std;
void printdev(libusb_device *dev);

int main() {
  libusb_device **devs;  // указатель на указатель на устройство,
                         // используется для получения списка устройств
  libusb_context *ctx = NULL;  // контекст сессии libusb
  int return_value;  // для возвращаемых значений
  ssize_t cnt;       // число найденных USB-устройств
  ssize_t i;  // индексная переменная цикла перебора всех устройств
  // инициализировать библиотеку libusb, открыть сессию работы с libusb
  return_value = libusb_init(&ctx);
  if (return_value < 0) {
    fprintf(stderr, "Ошибка: инициализация не выполнена, код: %d.\n",
            return_value);
    return 1;
  }
  // задать уровень подробности отладочных сообщений
  libusb_set_debug(ctx, 3);
  // получить список всех найденных USB- устройств
  cnt = libusb_get_device_list(ctx, &devs);
  if (cnt < 0) {
    fprintf(stderr, "Ошибка: список USB устройств не получен.\n", return_value);
    return 1;
  }
  // 6 10 10
  printf("Class |Vendor ID |Product ID     |Serial num     |Manufacturer\n");

  for (i = 0; i < cnt; i++) {  // цикл перебора всех устройств
    printdev(devs[i]);  // печать параметров устройства
  }

  // освободить память, выделенную функцией получения списка устройств
  libusb_free_device_list(devs, 1);
  libusb_exit(ctx);  // завершить работу с библиотекой libusb,
                     // закрыть сессию работы с libusb
  return 0;
}

void printdev(libusb_device *dev) {
  libusb_device_descriptor desc;  // дескриптор устройства
  libusb_device_handle *dev_handle;
  unsigned char serial[20] = {0};
  char *serial_ptr = (char *)(&(*serial));
  unsigned char manufacturer[50] = {0};
  char *man_ptr = (char *)(&(*manufacturer));
  int r = libusb_get_device_descriptor(dev, &desc);
  if (r < 0) {
    fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n", r);
    return;
  }

  r = libusb_open(dev, &dev_handle);
  r = libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer,
                                         manufacturer, 50);

  r = libusb_get_string_descriptor_ascii(dev_handle, desc.iSerialNumber, serial,
                                         20);
  string device_class, id_vendor, id_product, serial_num, manufacturer_str;
  device_class += to_string((int)desc.bDeviceClass);
  id_vendor += to_string(desc.idVendor);
  id_product += to_string(desc.idProduct);
  serial_num += serial_ptr;
  manufacturer_str += man_ptr;

  if (device_class.length() < TITLE1_LEN) {
    device_class += string(TITLE1_LEN - device_class.length(), ' ');
  }
  if (id_vendor.length() < TITLE2_LEN) {
    id_vendor += string(TITLE2_LEN - id_vendor.length(), ' ');
  }
  if (id_product.length() < TITLE3_LEN) {
    id_product += string(TITLE3_LEN - id_product.length(), ' ');
  }
  if (serial_num.length() < TITLE3_LEN) {
    serial_num += string(TITLE3_LEN - serial_num.length(), ' ');
  }
  if (manufacturer_str.length() < TITLE4_LEN) {
    manufacturer_str += string(TITLE4_LEN - manufacturer_str.length(), ' ');
  }

  cout << device_class << '|' << id_vendor << '|' << id_product << '|'
       << serial_num << '|' << manufacturer_str;
  cout << endl;
  libusb_close(dev_handle);
}
