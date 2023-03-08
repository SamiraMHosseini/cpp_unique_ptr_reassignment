#include <iostream>
#include <memory>

struct Base
{
	//Rule of 0
	virtual ~Base() = default;
	Base() = default;

	Base& operator=(const Base&) = default;
	Base(const Base&) = default;

	Base& operator=(Base&&) = default;
	Base(Base&&) = default;

	virtual void do_something() const
	{
		std::cout << "Base \n";
	}
};

struct Derived1 final : Base
{
	void do_something() const override
	{
		std::cout << "Derived1 \n";
	}

};

struct Derived2 final : Base
{
	void do_something() const override
	{
		std::cout << "Derived2 \n";
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

	//Verion1
	std::unique_ptr<Base> objectBase = make_object(Type::Base_Type);
	if (objectBase)
		objectBase->do_something();

	std::unique_ptr<Base> objectDerived1 = make_object(Type::Derived1_Type);

	if (objectDerived1)
		objectDerived1->do_something();

	std::unique_ptr<Base> objectDerived2 = make_object(Type::Derived2_Type);
	if (objectDerived2)
		objectDerived2->do_something();


	//Verion2
	std::unique_ptr<Base> object = make_object(Type::Base_Type);
	if (object)
		object->do_something();

	object = make_object(Type::Derived1_Type);
	if (object)
		object->do_something();


	object = make_object(Type::Derived2_Type);
	if (object)
		object->do_something();


	//Verion3
	auto object2 = make_object2(Type::Base_Type);
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
	delete object2;


}