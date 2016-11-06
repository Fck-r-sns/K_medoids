#ifndef KMEDOIDSCLUSTERING_H
#define KMEDOIDSCLUSTERING_H

#include <tuple>
#include <vector>
#include <functional>
#include <set>
#include <random>

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
    int getRandomTupleIndex(const std::set<int> &exceptions);

private:
    const Data *m_data = nullptr;
    int m_k = -1;
    DistanceFunc m_distanceFunc;

    std::random_device m_rd;
    std::mt19937 m_mt = { m_rd() };
    std::uniform_int_distribution<int> m_rand;
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
    if (!m_data) {
        throw std::logic_error("Data is NULL");
    }
    if (!m_distanceFunc) {
        throw std::logic_error("Distance function is undefined");
    }
    if (m_k == -1) {
        throw std::logic_error("Number of clusters is undefined");
    }
    if (m_k > m_data->size()) {
        throw std::logic_error("k must be higher than data size");
    }
    m_rand.param(decltype(m_rand)::param_type(0, m_data->size()));
    std::vector<Cluster> result;
    result.reserve(m_k);
    std::set<int> usedIndices;
    for (int i = 0; i < m_k; ++i) {
        int idx = getRandomTupleIndex(usedIndices);
        result.emplace_back({ m_data->at(idx) });
        usedIndices.insert(idx);
    }
}

template<typename... Types>
int KMedoidsClustering<Types...>::getRandomTupleIndex(const std::set<int> &exceptions)
{
    const int dataSize = m_data->size();
    int value, counter = 0;
    do {
        value = m_rand(m_mt);
        ++counter;
    } while (exceptions.find(value) != exceptions.cend() && counter < dataSize );
    if (counter > dataSize) {
        throw std::logic_error("Failed to get random tuple index");
    } else {
        return value;
    }
}

#endif // KMEDOIDSCLUSTERING_H
