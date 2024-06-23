#ifndef I2C_LCD_h
#define I2C_LCD_h
#define I2C_ADDR 0x27

class I2C_LCD
{
  public:
      I2C_LCD(unsigned int lcd_addr, unsigned int lcd_width, unsigned int lcd_height);
      void Initialise();
      void i2c_initialise();
      void lnOne_Cursor();
      void lnTwo_Cursor();
      void send_cmd(unsigned int value);
      void send_data(unsigned char value);
      void print_txt(char *str);
      void print_num(float num, int dec_places);
      void Cursor_off();
      void go_home();

  
  private:
      void send_byte(unsigned int value);
      void I2C_Write(unsigned int data);
      void I2C_Enable(unsigned int data);
      void send_data_cmd(unsigned int bits, unsigned int mode);
      unsigned int address;
      unsigned int width;
      unsigned int height;
};
#endif
