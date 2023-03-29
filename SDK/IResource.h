#pragma once
namespace core
{
	class IScriptRuntime;
	class IResource
	{
	protected:
		virtual ~IResource() = default;
	public:
		struct CreationInfo
		{
			std::string type;
			std::string name;
			std::string main;
			IPackage* pkg;
		};
		class Impl
		{
		public:
			virtual bool Start()
			{
				return true;
			};
			virtual bool Stop() { return true; };

			virtual void OnTick() {};

			virtual ~Impl() = default;
		};

		virtual IScriptRuntime* GetRuntime() const = 0;
		virtual Impl* GetImpl() const = 0;

		virtual bool IsStarted() const = 0;

		virtual const std::string& GetType() const = 0;
		virtual const std::string& GetName() const = 0;
		virtual const std::string& GetPath() const = 0;
		virtual const std::string& GetMain() const = 0;

		virtual IPackage* GetPackage() const = 0;
		//virtual MValueDict GetExports() const = 0;
		//virtual const Array<std::string> GetDependencies() const = 0;
		//virtual const Array<std::string> GetDependants() const = 0;
		//virtual const Array<Permission> GetRequiredPermissions() const = 0;
		//virtual const Array<Permission> GetOptionalPermissions() const = 0;

		//virtual void SetExports(MValueDict exports) = 0;
	};
} // namespace alt

