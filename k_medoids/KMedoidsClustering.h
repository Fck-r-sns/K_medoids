#ifndef KMEDOIDSCLUSTERING_H
#define KMEDOIDSCLUSTERING_H

#include <tuple>
#include <vector>
#include <functional>
#include <set>

template<typename... Types>
class KMedoidsClustering
{
public:
    using Tuple = std::tuple<Types...>;
    using Data = std::vector<Tuple>;
    using DistanceFunc = std::function<Tuple(const Tuple &, const Tuple &)>;

    class Cluster {
        Tuple center;
        std::set<int> indices; // indices of data objects which belongs to this cluster
    };

    static const int PROPERTY_COUNT = sizeof...(Types);

public:
    KMedoidsClustering &setData(const Data *data);
    KMedoidsClustering &setDistanceFunc(const DistanceFunc &func);
    KMedoidsClustering &setNumberOfClusters(int k);
    std::vector<Cluster> go();

private:
    const Data *m_data = nullptr;
    int m_k = -1;
    DistanceFunc m_distanceFunc;
};

template<typename... Types>
KMedoidsClustering<Types...> &KMedoidsClustering<Types...>::setData(const KMedoidsClustering::Data *data)
{
    m_data = data;
}

template<typename... Types>
KMedoidsClustering<Types...> &KMedoidsClustering<Types...>::setDistanceFunc(const DistanceFunc &func)
{
    m_distanceFunc = func;
}

template<typename... Types>
KMedoidsClustering<Types...> &KMedoidsClustering<Types...>::setNumberOfClusters(int k)
{
    m_k = k;
}

template<typename... Types>
std::vector<typename KMedoidsClustering<Types...>::Cluster> KMedoidsClustering<Types...>::go()
{

}

#endif // KMEDOIDSCLUSTERING_H
