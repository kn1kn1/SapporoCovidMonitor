// Generated by rstantools.  Do not edit by hand.

/*
    SapporoCovidMonitor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SapporoCovidMonitor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SapporoCovidMonitor.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MODELS_HPP
#define MODELS_HPP
#define STAN__SERVICES__COMMAND_HPP
#include <rstan/rstaninc.hpp>
// Code generated by Stan version 2.21.0
#include <stan/model/model_header.hpp>
namespace model_tokbsts_namespace {
using std::istream;
using std::string;
using std::stringstream;
using std::vector;
using stan::io::dump;
using stan::math::lgamma;
using stan::model::prob_grad;
using namespace stan::math;
static int current_statement_begin__;
stan::io::program_reader prog_reader__() {
    stan::io::program_reader reader;
    reader.add_event(0, 0, "start", "model_tokbsts");
    reader.add_event(31, 29, "end", "model_tokbsts");
    return reader;
}
#include <stan_meta_header.hpp>
class model_tokbsts
  : public stan::model::model_base_crtp<model_tokbsts> {
private:
        int N;
        std::vector<double> y;
public:
    model_tokbsts(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : model_base_crtp(0) {
        ctor_body(context__, 0, pstream__);
    }
    model_tokbsts(stan::io::var_context& context__,
        unsigned int random_seed__,
        std::ostream* pstream__ = 0)
        : model_base_crtp(0) {
        ctor_body(context__, random_seed__, pstream__);
    }
    void ctor_body(stan::io::var_context& context__,
                   unsigned int random_seed__,
                   std::ostream* pstream__) {
        typedef double local_scalar_t__;
        boost::ecuyer1988 base_rng__ =
          stan::services::util::create_rng(random_seed__, 0);
        (void) base_rng__;  // suppress unused var warning
        current_statement_begin__ = -1;
        static const char* function__ = "model_tokbsts_namespace::model_tokbsts";
        (void) function__;  // dummy to suppress unused var warning
        size_t pos__;
        (void) pos__;  // dummy to suppress unused var warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        try {
            // initialize data block variables from context__
            current_statement_begin__ = 2;
            context__.validate_dims("data initialization", "N", "int", context__.to_vec());
            N = int(0);
            vals_i__ = context__.vals_i("N");
            pos__ = 0;
            N = vals_i__[pos__++];
            check_greater_or_equal(function__, "N", N, 0);
            current_statement_begin__ = 3;
            validate_non_negative_index("y", "N", N);
            context__.validate_dims("data initialization", "y", "double", context__.to_vec(N));
            y = std::vector<double>(N, double(0));
            vals_r__ = context__.vals_r("y");
            pos__ = 0;
            size_t y_k_0_max__ = N;
            for (size_t k_0__ = 0; k_0__ < y_k_0_max__; ++k_0__) {
                y[k_0__] = vals_r__[pos__++];
            }
            size_t y_i_0_max__ = N;
            for (size_t i_0__ = 0; i_0__ < y_i_0_max__; ++i_0__) {
                check_greater_or_equal(function__, "y[i_0__]", y[i_0__], 0);
            }
            // initialize transformed data variables
            // execute transformed data statements
            // validate transformed data
            // validate, set parameter ranges
            num_params_r__ = 0U;
            param_ranges_i__.clear();
            current_statement_begin__ = 7;
            validate_non_negative_index("season", "N", N);
            num_params_r__ += (1 * N);
            current_statement_begin__ = 8;
            validate_non_negative_index("trend", "N", N);
            num_params_r__ += (1 * N);
            current_statement_begin__ = 9;
            num_params_r__ += 1;
            current_statement_begin__ = 10;
            num_params_r__ += 1;
            current_statement_begin__ = 11;
            num_params_r__ += 1;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    ~model_tokbsts() { }
    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__,
                         std::ostream* pstream__) const {
        typedef double local_scalar_t__;
        stan::io::writer<double> writer__(params_r__, params_i__);
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;
        current_statement_begin__ = 7;
        if (!(context__.contains_r("season")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable season missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("season");
        pos__ = 0U;
        validate_non_negative_index("season", "N", N);
        context__.validate_dims("parameter initialization", "season", "double", context__.to_vec(N));
        std::vector<double> season(N, double(0));
        size_t season_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < season_k_0_max__; ++k_0__) {
            season[k_0__] = vals_r__[pos__++];
        }
        size_t season_i_0_max__ = N;
        for (size_t i_0__ = 0; i_0__ < season_i_0_max__; ++i_0__) {
            try {
                writer__.scalar_unconstrain(season[i_0__]);
            } catch (const std::exception& e) {
                stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable season: ") + e.what()), current_statement_begin__, prog_reader__());
            }
        }
        current_statement_begin__ = 8;
        if (!(context__.contains_r("trend")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable trend missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("trend");
        pos__ = 0U;
        validate_non_negative_index("trend", "N", N);
        context__.validate_dims("parameter initialization", "trend", "double", context__.to_vec(N));
        std::vector<double> trend(N, double(0));
        size_t trend_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < trend_k_0_max__; ++k_0__) {
            trend[k_0__] = vals_r__[pos__++];
        }
        size_t trend_i_0_max__ = N;
        for (size_t i_0__ = 0; i_0__ < trend_i_0_max__; ++i_0__) {
            try {
                writer__.scalar_unconstrain(trend[i_0__]);
            } catch (const std::exception& e) {
                stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable trend: ") + e.what()), current_statement_begin__, prog_reader__());
            }
        }
        current_statement_begin__ = 9;
        if (!(context__.contains_r("s_trend")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable s_trend missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("s_trend");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "s_trend", "double", context__.to_vec());
        double s_trend(0);
        s_trend = vals_r__[pos__++];
        try {
            writer__.scalar_unconstrain(s_trend);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable s_trend: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 10;
        if (!(context__.contains_r("s_season")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable s_season missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("s_season");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "s_season", "double", context__.to_vec());
        double s_season(0);
        s_season = vals_r__[pos__++];
        try {
            writer__.scalar_unconstrain(s_season);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable s_season: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 11;
        if (!(context__.contains_r("s_q")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable s_q missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("s_q");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "s_q", "double", context__.to_vec());
        double s_q(0);
        s_q = vals_r__[pos__++];
        try {
            writer__.scalar_unconstrain(s_q);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable s_q: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }
    void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double, Eigen::Dynamic, 1>& params_r,
                         std::ostream* pstream__) const {
      std::vector<double> params_r_vec;
      std::vector<int> params_i_vec;
      transform_inits(context, params_i_vec, params_r_vec, pstream__);
      params_r.resize(params_r_vec.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r(i) = params_r_vec[i];
    }
    template <bool propto__, bool jacobian__, typename T__>
    T__ log_prob(std::vector<T__>& params_r__,
                 std::vector<int>& params_i__,
                 std::ostream* pstream__ = 0) const {
        typedef T__ local_scalar_t__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // dummy to suppress unused var warning
        T__ lp__(0.0);
        stan::math::accumulator<T__> lp_accum__;
        try {
            stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
            // model parameters
            current_statement_begin__ = 7;
            std::vector<local_scalar_t__> season;
            size_t season_d_0_max__ = N;
            season.reserve(season_d_0_max__);
            for (size_t d_0__ = 0; d_0__ < season_d_0_max__; ++d_0__) {
                if (jacobian__)
                    season.push_back(in__.scalar_constrain(lp__));
                else
                    season.push_back(in__.scalar_constrain());
            }
            current_statement_begin__ = 8;
            std::vector<local_scalar_t__> trend;
            size_t trend_d_0_max__ = N;
            trend.reserve(trend_d_0_max__);
            for (size_t d_0__ = 0; d_0__ < trend_d_0_max__; ++d_0__) {
                if (jacobian__)
                    trend.push_back(in__.scalar_constrain(lp__));
                else
                    trend.push_back(in__.scalar_constrain());
            }
            current_statement_begin__ = 9;
            local_scalar_t__ s_trend;
            (void) s_trend;  // dummy to suppress unused var warning
            if (jacobian__)
                s_trend = in__.scalar_constrain(lp__);
            else
                s_trend = in__.scalar_constrain();
            current_statement_begin__ = 10;
            local_scalar_t__ s_season;
            (void) s_season;  // dummy to suppress unused var warning
            if (jacobian__)
                s_season = in__.scalar_constrain(lp__);
            else
                s_season = in__.scalar_constrain();
            current_statement_begin__ = 11;
            local_scalar_t__ s_q;
            (void) s_q;  // dummy to suppress unused var warning
            if (jacobian__)
                s_q = in__.scalar_constrain(lp__);
            else
                s_q = in__.scalar_constrain();
            // model body
            {
            current_statement_begin__ = 15;
            validate_non_negative_index("q", "N", N);
            std::vector<local_scalar_t__  > q(N, local_scalar_t__(DUMMY_VAR__));
            stan::math::initialize(q, DUMMY_VAR__);
            stan::math::fill(q, DUMMY_VAR__);
            current_statement_begin__ = 16;
            validate_non_negative_index("cum_trend", "N", N);
            std::vector<local_scalar_t__  > cum_trend(N, local_scalar_t__(DUMMY_VAR__));
            stan::math::initialize(cum_trend, DUMMY_VAR__);
            stan::math::fill(cum_trend, DUMMY_VAR__);
            current_statement_begin__ = 17;
            for (int i = 7; i <= N; ++i) {
                current_statement_begin__ = 18;
                lp_accum__.add(normal_log<propto__>(get_base1(season, i, "season", 1), (((((-(get_base1(season, (i - 1), "season", 1)) - get_base1(season, (i - 2), "season", 1)) - get_base1(season, (i - 3), "season", 1)) - get_base1(season, (i - 4), "season", 1)) - get_base1(season, (i - 5), "season", 1)) - get_base1(season, (i - 6), "season", 1)), s_season));
            }
            current_statement_begin__ = 19;
            for (int i = 3; i <= N; ++i) {
                current_statement_begin__ = 20;
                lp_accum__.add(normal_log<propto__>(get_base1(trend, i, "trend", 1), ((2 * get_base1(trend, (i - 1), "trend", 1)) - get_base1(trend, (i - 2), "trend", 1)), s_trend));
            }
            current_statement_begin__ = 22;
            stan::model::assign(cum_trend, 
                        stan::model::cons_list(stan::model::index_uni(1), stan::model::nil_index_list()), 
                        get_base1(trend, 1, "trend", 1), 
                        "assigning variable cum_trend");
            current_statement_begin__ = 23;
            for (int i = 2; i <= N; ++i) {
                current_statement_begin__ = 24;
                stan::model::assign(cum_trend, 
                            stan::model::cons_list(stan::model::index_uni(i), stan::model::nil_index_list()), 
                            (get_base1(cum_trend, (i - 1), "cum_trend", 1) + get_base1(trend, i, "trend", 1)), 
                            "assigning variable cum_trend");
            }
            current_statement_begin__ = 25;
            for (int i = 1; i <= N; ++i) {
                current_statement_begin__ = 26;
                stan::model::assign(q, 
                            stan::model::cons_list(stan::model::index_uni(i), stan::model::nil_index_list()), 
                            ((get_base1(y, i, "y", 1) - get_base1(season, i, "season", 1)) - get_base1(cum_trend, i, "cum_trend", 1)), 
                            "assigning variable q");
            }
            current_statement_begin__ = 27;
            for (int i = 1; i <= N; ++i) {
                current_statement_begin__ = 28;
                lp_accum__.add(normal_log<propto__>(get_base1(q, i, "q", 1), 0, s_q));
            }
            }
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
        lp_accum__.add(lp__);
        return lp_accum__.sum();
    } // log_prob()
    template <bool propto, bool jacobian, typename T_>
    T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
               std::ostream* pstream = 0) const {
      std::vector<T_> vec_params_r;
      vec_params_r.reserve(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        vec_params_r.push_back(params_r(i));
      std::vector<int> vec_params_i;
      return log_prob<propto,jacobian,T_>(vec_params_r, vec_params_i, pstream);
    }
    void get_param_names(std::vector<std::string>& names__) const {
        names__.resize(0);
        names__.push_back("season");
        names__.push_back("trend");
        names__.push_back("s_trend");
        names__.push_back("s_season");
        names__.push_back("s_q");
    }
    void get_dims(std::vector<std::vector<size_t> >& dimss__) const {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dims__.push_back(N);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(N);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
    }
    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) const {
        typedef double local_scalar_t__;
        vars__.resize(0);
        stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
        static const char* function__ = "model_tokbsts_namespace::write_array";
        (void) function__;  // dummy to suppress unused var warning
        // read-transform, write parameters
        std::vector<double> season;
        size_t season_d_0_max__ = N;
        season.reserve(season_d_0_max__);
        for (size_t d_0__ = 0; d_0__ < season_d_0_max__; ++d_0__) {
            season.push_back(in__.scalar_constrain());
        }
        size_t season_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < season_k_0_max__; ++k_0__) {
            vars__.push_back(season[k_0__]);
        }
        std::vector<double> trend;
        size_t trend_d_0_max__ = N;
        trend.reserve(trend_d_0_max__);
        for (size_t d_0__ = 0; d_0__ < trend_d_0_max__; ++d_0__) {
            trend.push_back(in__.scalar_constrain());
        }
        size_t trend_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < trend_k_0_max__; ++k_0__) {
            vars__.push_back(trend[k_0__]);
        }
        double s_trend = in__.scalar_constrain();
        vars__.push_back(s_trend);
        double s_season = in__.scalar_constrain();
        vars__.push_back(s_season);
        double s_q = in__.scalar_constrain();
        vars__.push_back(s_q);
        double lp__ = 0.0;
        (void) lp__;  // dummy to suppress unused var warning
        stan::math::accumulator<double> lp_accum__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        if (!include_tparams__ && !include_gqs__) return;
        try {
            if (!include_gqs__ && !include_tparams__) return;
            if (!include_gqs__) return;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    template <typename RNG>
    void write_array(RNG& base_rng,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                     bool include_tparams = true,
                     bool include_gqs = true,
                     std::ostream* pstream = 0) const {
      std::vector<double> params_r_vec(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r_vec[i] = params_r(i);
      std::vector<double> vars_vec;
      std::vector<int> params_i_vec;
      write_array(base_rng, params_r_vec, params_i_vec, vars_vec, include_tparams, include_gqs, pstream);
      vars.resize(vars_vec.size());
      for (int i = 0; i < vars.size(); ++i)
        vars(i) = vars_vec[i];
    }
    std::string model_name() const {
        return "model_tokbsts";
    }
    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        size_t season_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < season_k_0_max__; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "season" << '.' << k_0__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t trend_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < trend_k_0_max__; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "trend" << '.' << k_0__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "s_trend";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "s_season";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "s_q";
        param_names__.push_back(param_name_stream__.str());
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
        }
        if (!include_gqs__) return;
    }
    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        size_t season_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < season_k_0_max__; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "season" << '.' << k_0__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t trend_k_0_max__ = N;
        for (size_t k_0__ = 0; k_0__ < trend_k_0_max__; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "trend" << '.' << k_0__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "s_trend";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "s_season";
        param_names__.push_back(param_name_stream__.str());
        param_name_stream__.str(std::string());
        param_name_stream__ << "s_q";
        param_names__.push_back(param_name_stream__.str());
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
        }
        if (!include_gqs__) return;
    }
}; // model
}  // namespace
typedef model_tokbsts_namespace::model_tokbsts stan_model;
#ifndef USING_R
stan::model::model_base& new_model(
        stan::io::var_context& data_context,
        unsigned int seed,
        std::ostream* msg_stream) {
  stan_model* m = new stan_model(data_context, seed, msg_stream);
  return *m;
}
#endif
#endif
