#ifndef EXCEPTIONCONFIGURE_H_
#define EXCEPTIONCONFIGURE_H_

//namespace Common{

class ExceptionConfigure {
public:
  ExceptionConfigure();
  virtual ~ExceptionConfigure();
  //Exception Configuration
  void setExceptionFlag(bool);
  bool usingException() const;

private:
  bool usingException_;
};

//}//namespace Common
#endif /* EXCEPTIONCONFIGURE_H_ */
