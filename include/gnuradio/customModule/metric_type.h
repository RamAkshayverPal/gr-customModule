#ifndef INCLUDED_CUSTOMMODULE_METRIC_TYPE_H
#define INCLUDED_CUSTOMMODULE_METRIC_TYPE_H

namespace gr {
namespace customModule {

typedef enum {
    TRELLIS_EUCLIDEAN = 200,
    TRELLIS_HARD_SYMBOL,
    TRELLIS_HARD_BIT
} trellis_metric_type_t;

} /* namespace customModule */
} /* namespace gr */

#endif /* INCLUDED_DIGITAL_METRIC_TYPE_H */
