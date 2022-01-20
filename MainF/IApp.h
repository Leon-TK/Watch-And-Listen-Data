/*    
* Main facade of program
*/    
namespace WAL
{
	class IApp
	{
	public:
		virtual ~IApp() {};
		virtual void Run() = 0;
		virtual void Init() = 0;
		virtual void Shutdown() = 0;

	};
}

