#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include <tuple>
#include <vector>
#include <functional>
#include <set>

template<typename... Types>
class KMeansClustering
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
    KMeansClustering &setData(const Data *data);
    KMeansClustering &setDistanceFunc(const DistanceFunc &func);
    KMeansClustering &setNumberOfClusters(int k);
    std::vector<Cluster> go();

private:
    const Data *m_data = nullptr;
    int m_k = -1;
    DistanceFunc m_distanceFunc;
};

template<typename... Types>
KMeansClustering<Types...> &KMeansClustering<Types...>::setData(const KMeansClustering::Data *data)
{
    m_data = data;
}

template<typename... Types>
KMeansClustering<Types...> &KMeansClustering<Types...>::setDistanceFunc(const DistanceFunc &func)
{
    m_distanceFunc = func;
}

template<typename... Types>
KMeansClustering<Types...> &KMeansClustering<Types...>::setNumberOfClusters(int k)
{
    m_k = k;
}

template<typename... Types>
std::vector<typename KMeansClustering<Types...>::Cluster> KMeansClustering<Types...>::go()
{

}

#endif // KMEANSCLUSTERING_H
