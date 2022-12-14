#ifndef CORRESPONDENCEFILTER_HPP
#define CORRESPONDENCEFILTER_HPP

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <stdio.h>
#include "../global.hpp"
#include "NeighbourFinder.hpp"
#include "helper_functions.hpp"
#include "BaseCorrespondenceFilter.hpp"

typedef Eigen::VectorXf VecDynFloat;
typedef Eigen::Matrix< float, Eigen::Dynamic, registration::NUM_FEATURES> FeatureMat; //matrix Mx6 of type float
typedef Eigen::Matrix< float, 1, registration::NUM_FEATURES> FeatureVec; //matrix Mx6 of type float
typedef Eigen::Vector3f Vec3Float;
typedef Eigen::SparseMatrix<float, 0, int> SparseMat;
typedef Eigen::Triplet<float> Triplet;
typedef Eigen::Matrix< int, Eigen::Dynamic, Eigen::Dynamic> MatDynInt; //matrix MxN of type unsigned int
typedef Eigen::Matrix< float, Eigen::Dynamic, Eigen::Dynamic> MatDynFloat;

namespace registration {

class CorrespondenceFilter : public BaseCorrespondenceFilter
{

    /*
    # GOAL
    For each element in inFloatingFeatures, we're going to find corresponding
    features in the elements of inTargetFeatures.
    The used weight is one over the distance squared.

    # INPUTS
    -inFloatingFeatures
    -inTargetFeatures
    -inTargetFlags

    # PARAMETERS
    -numNeighbours(=3):
    number of nearest neighbours
    -flagThreshold:
    threshold that the weighted corresponding flag needs to make in order to be flagged as 1.0.
    Otherwise, it receives flag 0.0f.

    # OUTPUT
    -outCorrespondingFeatures
    -outCorrespondingFlags
    */

    public:
        //CorrespondenceFilter(); //default constructor
        //~CorrespondenceFilter(); //destructor

        void set_floating_input(const FeatureMat * const inFloatingFeatures,
                                const VecDynFloat * const inFloatingFlags);
        void set_target_input(const FeatureMat * const inTargetFeatures,
                            const VecDynFloat * const inTargetFlags);
        SparseMat get_affinity() const {return _affinity;}
        void set_parameters(const size_t numNeighbours,
                            const float flagThreshold);
        void set_affinity_normalization(const bool normalizeAffinity = true);
        void update();

    protected:

    private:

        //# Internal Data structures
        NeighbourFinder<FeatureMat> _neighbourFinder;

        //# Internal Parameters
        size_t _numAffinityElements = 0;
        //# Normalize affinity matrix
        bool _normalizeAffinity = true;

        //# Internal Functions
        //## Function to update the sparse affinity matrix
        void _update_affinity();
        //## Function to convert the sparse affinity weights into corresponding
        //## features and flags
        void _affinity_to_correspondences();

};




}//namespace registration

#endif // CORRESPONDENCEFILTER_HPP
