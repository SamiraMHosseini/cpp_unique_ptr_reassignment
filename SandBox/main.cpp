#include <iostream>
#include <memory>

struct Base
{
	//Rule of 0
	virtual ~Base()
	{
		std::cout << "~Base \n";
	}
	Base() = default;

	Base& operator=(const Base&) = default;
	Base(const Base&) = default;

	Base& operator=(Base&&) = default;
	Base(Base&&) = default;

	virtual void do_something()
	{
		std::cout << "Base \n";
	}
};

struct Derived1 final : Base
{
	void do_something()  override
	{
		std::cout << "Derived1 \n";
	}
	virtual ~Derived1()
	{
		std::cout << "~Derived1 \n";
	}
};

struct Derived2 final : Base
{
	void do_something()  override
	{
		std::cout << "Derived2 \n";
	}
	virtual ~Derived2()
	{
		std::cout << "~Derived2 \n";
	}
};

enum class Type
{
	Base_Type,

	Derived1_Type,

	Derived2_Type
};
std::unique_ptr<Base> make_object(const Type& classType)
{
	switch (classType)
	{

	case Type::Base_Type:
		return std::make_unique<Base>();

	case Type::Derived1_Type:
		return std::make_unique<Derived1>();

	case Type::Derived2_Type:
		return std::make_unique<Derived2>();

	default:
		return nullptr;
	}

}

Base* make_object2(const Type& classType)
{
	switch (classType)
	{

	case Type::Base_Type:
		return new Base();

	case Type::Derived1_Type:
		return new Derived1();

	case Type::Derived2_Type:
		return new Derived2();

	default:
		return nullptr;
	}

}
int main()
{

	std::unique_ptr<Base> object = make_object(Type::Base_Type);
	if (object)
		object->do_something();

	std::cout << "***************************************** \n";

	 object = make_object(Type::Derived1_Type);
	object->do_something();

	std::cout << "***************************************** \n";
	object = make_object(Type::Derived2_Type);
	if (object)
		object->do_something();

	std::cout << "***************************************** \n";

	/*auto object2 = make_object2(Type::Base_Type);
	if (object2)
		object2->do_something();
	delete object2;

	object2 = make_object2(Type::Derived1_Type);
	if (object2)
		object2->do_something();
	delete object2;

	object2 = make_object2(Type::Derived2_Type);
	if (object2)
		object2->do_something();
	delete object2;*/

}