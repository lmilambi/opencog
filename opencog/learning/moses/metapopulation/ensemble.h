/**
 * ensemble.h ---
 *
 * Copyright (C) 2014 Aidyia Limited
 *
 * Authors: Linas Vepstas
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _OPENCOG_ENSEMBLE_H
#define _OPENCOG_ENSEMBLE_H

#include "../moses/types.h"  // for scored_combo_tree
#include "../scoring/behave_cscore.h"
#include "../scoring/boosting_ascore.h"

namespace opencog {
namespace moses {

/**
 * The ensemble holds a collection of the fittest combo trees.  The
 * goal of the ensemble is to provide the best (most accurate, most
 * predictive) model of the training data.  The ensemble is meant to
 * be creted during training, and used for inference after training.
 *
 * The ensemble should be contrasted with the metapopulation, which
 * also holds a collection of combo trees. However, the metapopulation
 * is meant to do something different: to provide the 'breeding stock'
 * for deme expansion and optimization.  Therefore, the metapopulation
 * management policy is different from the ensemble, although it is 
 * likely that the two will hold similar contents. The ensemble is
 * intended for inference; the metapopulation for breeding.
 *
 * In particular (depending on paramters) the ensemble is designed to
 * hold a boosted collection of combo trees.  A boosted set of trees
 * only makes sense when the set was generated using a consisten
 * algorithm, admitting only certain specific members. This differs
 * from the metapopulation, which has no particular admission criteria.
 *
 * XXX FIXME: right now, the ensemble is attached to the metapop, its
 * kind-of coming along for the ride, because that's easier for now.
 * Someday, it should have an independent existance.
 */

struct ensemble_parameters
{
	ensemble_parameters() :
		num_to_promote(1)
	{}

	int num_to_promote;  // max number of demes to accept into ensemble,
	                     // per learning iteration.

};

class ensemble
{
public:
    ensemble(behave_cscore&,
             const ensemble_parameters& ep = ensemble_parameters());

    // Should this be the right interface ?? Similar to metapop ...
    // void add_deme(deme_t&, const representation&);

    void add_candidates(scored_combo_tree_set&);

    const scored_combo_tree_set& get_ensemble() const {
        return _scored_trees;
    }

private:
    const ensemble_parameters& _params;
    boosting_ascore* _booster;

    scored_combo_tree_set _scored_trees;
};

}}; // namespace opencog::moses

#endif // _OPENCOG_ENSEMBLE_H


