

#include "domains/polyhedra.h"
#include "utils/lipschitz.h"
#include "utils/constants.h"
#include "transforms/transformation.h"
#include "transforms/interpolation.h"
#include "transforms/parser.h"
#include <vector>
#include <string>

extern "C" {
using namespace std;

class TransformAttackContainer{

    public:
        // ---- Constructors
        TransformAttackContainer(double noise,
                                    int n_splits,
                                    int inside_splits,
                                    int nRows,
                                    int nCols,
                                    int nChannels,
                                    string calc_type,
                                    string images,
                                    SpatialTransformation& spatialTransformation,
                                    PixelTransformation& pixelTransformation,
                                    bool debug,
                                    vector<vector<double> > splitPoints);

        // ---- Members set by Constructor
        double noise;
        int n_splits, inside_splits, nRows, nCols, nChannels;
        string calc_type, images;
        bool debug;
        vector<vector<double> > splitPoints;
        SpatialTransformation& spatialTransformation;
        PixelTransformation& pixelTransformation;
        const InterpolationTransformation& interpolationTransformation = InterpolationTransformation();

        // ---- Members set by Methods
        vector<vector<double> > transform_vector, attack_param_vector, attack_image_vector;
        vector<int> transform_vector_dim_1;

        // ---- Methods
        void setTransformationsAndAttacksFor(int image_number);
};
TransformAttackContainer* getTransformAttackContainer(char* config);

void setTransformationsAndAttacksFor(TransformAttackContainer& container, int image_number) {
    container.setTransformationsAndAttacksFor(image_number);
};

vector<double>* get_transformations(TransformAttackContainer& container) {
    return container.transform_vector.data();
};

int get_transformations_dim_0(TransformAttackContainer& container) {
    return container.transform_vector.size();
};

int* get_transformations_dim_1(TransformAttackContainer& container) {
    container.transform_vector_dim_1.clear();
    for (const auto v:container.transform_vector) {
        container.transform_vector_dim_1.push_back(v.size());
    }
    return container.transform_vector_dim_1.data();
};

// this works because vectors are continuous in memory
vector<double>* get_attack_params(TransformAttackContainer& container) {
    return container.attack_param_vector.data();
};

int get_attack_params_dim_0(TransformAttackContainer& container) {
    return container.attack_param_vector.size();
};

int get_attack_params_dim_1(TransformAttackContainer& container) {
    return container.attack_param_vector[0].size();
};

vector<double>* get_attack_images(TransformAttackContainer& container) {
    return container.attack_image_vector.data();
};

int get_attack_images_dim_0(TransformAttackContainer& container) {
    return container.attack_image_vector.size();
};

int get_attack_images_dim_1(TransformAttackContainer& container) {
    return container.attack_image_vector[0].size();
};
} // end extern "C"