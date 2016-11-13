#ifndef KMEDOIDSCLUSTERING_H
#define KMEDOIDSCLUSTERING_H

#include <tuple>
#include <vector>
#include <functional>
#include <set>
#include <random>
#include <algorithm>

template<typename... Types>
class KMedoidsClustering
{
public:
    using Tuple = std::tuple<Types...>;
    using Data = std::vector<Tuple>;
    using DistanceFunc = std::function<double(const Tuple &, const Tuple &)>;

    struct Cluster {
        Tuple center;
        std::set<int> indices; // indices of data objects which belongs to this cluster

        Cluster(const Tuple &center) : center(center) {}
    };

    static const int PROPERTY_COUNT = sizeof...(Types);

public:
    KMedoidsClustering();
    KMedoidsClustering &setData(const Data *data);
    KMedoidsClustering &setDistanceFunc(const DistanceFunc &func);
    KMedoidsClustering &setNumberOfClusters(int k);
    std::vector<Cluster> go();

private:
    int getRandomTupleIndex(const std::set<int> &exceptions);
    double calculateDistanceSumWithinCluster(const Tuple &tuple, const Cluster &cluster);

private:
    const Data *m_data = nullptr;
    int m_k = -1;
    DistanceFunc m_distanceFunc;

    std::random_device m_rd;
    std::mt19937 m_mt;
    std::uniform_int_distribution<int> m_rand;
};

template<typename... Types>
KMedoidsClustering<Types...>::KMedoidsClustering() :
    m_mt(m_rd())
{
}

template<typename... Types>
KMedoidsClustering<Types...> &KMedoidsClustering<Types...>::setData(const KMedoidsClustering::Data *data)
{
    m_data = data;
    return *this;
}

template<typename... Types>
KMedoidsClustering<Types...> &KMedoidsClustering<Types...>::setDistanceFunc(const DistanceFunc &func)
{
    m_distanceFunc = func;
    return *this;
}

template<typename... Types>
KMedoidsClustering<Types...> &KMedoidsClustering<Types...>::setNumberOfClusters(int k)
{
    m_k = k;
    return *this;
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
    if (m_k < 0) {
        throw std::logic_error("Number of clusters is undefined");
    }
    const auto dataSize = m_data->size();
    if (m_k > (int)dataSize) {
        throw std::logic_error("k can not be higher than data size");
    }

    // init random number generator
    m_rand.param(typename decltype(m_rand)::param_type(0, m_data->size()));
    std::vector<Cluster> clusters;
    clusters.reserve(m_k);
    std::set<int> usedIndices;
    for (int i = 0; i < m_k; ++i) {
        int idx = getRandomTupleIndex(usedIndices);
        clusters.emplace_back(m_data->at(idx));
        usedIndices.insert(idx);
    }
    bool centersChanged = false;
    do {
        // clear clusters, new iteration
        for (Cluster &c : clusters) {
            c.indices.clear();
        }

        // distribute objects between clusters
        std::vector<double> distances;
        distances.reserve(m_k);
        for (size_t dataObjectIdx = 0; dataObjectIdx < dataSize; ++dataObjectIdx) {
            const Tuple &t = m_data->at(dataObjectIdx);
            distances.clear();
            for (const Cluster &c : clusters) {
                distances.emplace_back(m_distanceFunc(c.center, t));
            }
            const auto min = std::min_element(distances.cbegin(), distances.cend());
            if (min == distances.cend()) {
                throw std::logic_error("Failed to find nearest center");
            }
            const int nearestClusterIndex = std::distance(distances.cbegin(), min);
            clusters.at(nearestClusterIndex).indices.insert(dataObjectIdx);
        }

        // find new medoids
        centersChanged = false;
        for (Cluster &c : clusters) {
            double medoidDistance = calculateDistanceSumWithinCluster(c.center, c);
            for (int medoidCandidateIdx : c.indices) {
                const Tuple &medoidCandidate = m_data->at(medoidCandidateIdx);
                const double dst = calculateDistanceSumWithinCluster(medoidCandidate, c);
                if (dst < medoidDistance) {
                    c.center = medoidCandidate;
                    medoidDistance = dst;
                    centersChanged = true;
                }
            }
        }

    } while (centersChanged);

    return clusters;
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

template<typename... Types>
double KMedoidsClustering<Types...>::calculateDistanceSumWithinCluster(const Tuple &from, const Cluster &cluster)
{
    double distanceSum;
    for (int tupleIdx : cluster.indices) {
        const Tuple &t = m_data->at(tupleIdx);
        distanceSum += m_distanceFunc(from, t);
    }
    return distanceSum;
}

#endif // KMEDOIDSCLUSTERING_H
