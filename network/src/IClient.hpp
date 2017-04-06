#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

namespace arcade
{
  namespace Network
  {
    class IClient
    {
    public:
      enum ClientAction
	{
	  SUCCESS,
	  FAILURE,
	  DISCONNECT
	};

      virtual ~IClient(){};
      virtual bool	disconnect() = 0;
      virtual IClient::ClientAction read() = 0;
    };
  }
}

#endif // !ICLIENT_HPP_
