#ifndef LOCATOR_SERVICE_HPP
#define LOCATOR_SERVICE_HPP


#include <iostream>
#include <memory>
#include <unordered_map>


class ServiceLocator
{
public:
    template<typename InstanceType, typename InterfaceType = InstanceType>
	static void instantiate();

    template<typename InstanceType, typename InterfaceType = InstanceType>
    static void instantiate(std::shared_ptr<void> instance);
	
    template<typename InstanceType>
	static std::shared_ptr<InstanceType> resolve();

private:
	static std::unordered_map<size_t, std::shared_ptr<void>> _instances;
};


template<typename InstanceType, typename InterfaceType = InstanceType>
void ServiceLocator::instantiate()
{
    const size_t hash = typeid(InterfaceType).hash_code();
    if (ServiceLocator::_instances.find(hash) == ServiceLocator::_instances.end())
    {
        InstanceType* instance = new InstanceType();
        ServiceLocator::_instances.emplace(hash, std::shared_ptr<void>(instance));
    }
}


template<typename InstanceType, typename InterfaceType = InstanceType>
void ServiceLocator::instantiate(std::shared_ptr<void> instance)
{
    const size_t hash = typeid(InterfaceType).hash_code();
    if (ServiceLocator::_instances.find(hash) == ServiceLocator::_instances.end())
        ServiceLocator::_instances.emplace(hash, instance);
}


template<typename InstanceType>
std::shared_ptr<InstanceType> ServiceLocator::resolve()
{
    const size_t hash = typeid(InstanceType).hash_code();
    auto it = ServiceLocator::_instances.find(hash);
    if (it != ServiceLocator::_instances.end())
        return std::static_pointer_cast<InstanceType>(it->second);
    return {};
}



#endif  // LOCATOR_SERVICE_HPP
