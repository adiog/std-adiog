// This file is a part of cppstat project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef CPPSTAT_PLOT_H
#define CPPSTAT_PLOT_H

#include "../../common/MathTypes.h"
#include "gnuplot-iostream.h"

namespace math {
namespace plot {

using FunctionGraphRefs =
    std::vector<std::reference_wrapper<const FunctionGraph>>;
using LabelRefs = std::vector<std::reference_wrapper<const std::string>>;
using FunctionGraphs = std::vector<FunctionGraph>;
using Labels = std::vector<std::string>;

class Plot
{
public:
    Plot()
            : graphs{}
            , labels{} {};

    void addFunctionGraph(const FunctionGraph &graph,
                          const std::string &label)
    {
        this->graphs.emplace_back(graph);
        this->labels.emplace_back(label);
    }

    void render(std::string label = "")
    {
        Gnuplot gp;
        Plot::init(label, gp);
        gp << "plot ";
        for (auto labelIt = labels.begin();
             labelIt < labels.end() - 1;
             labelIt++)
        {
            gp << "'-' with lines";
            if (*labelIt != "")
            {
                gp << " title '" << *labelIt << "'";
            }
            gp << ", ";
        }
        gp << "'-' with lines";
        if (labels.back() != "")
        {
            gp << " title '" << labels.back();
        }
        gp << "\n";
        for (const auto &graph : graphs)
        {
            gp.send1d(graph);
        }
    }

    void reset(void)
    {
        graphs.clear();
        labels.clear();
    }

    template <class... Args>
    static void renderPlots(const Args &... args)
    {
        Gnuplot gp;
        Plot::init("", gp);
        FunctionGraphRefs graphs;
        LabelRefs labels;
        Plot::renderCollect(gp, graphs, labels, args...);
    }

private:
    static void init(std::string label, Gnuplot &gp, Real xrange_min = -1.0, Real xrange_max = 10.0, Real yrange_min = -5.0, Real yrange_max = 5.0)
    {
#ifdef __CYGWIN32__
        gp << "set terminal dumb\n";
#endif
        gp << "set title '" << label << "'\n";
        gp << "unset key\n";
        gp << "set arrow from -1,0 to 10,0\n";
        gp << "set arrow from 0,-5 to 0,5\n";
        gp << "set xrange [" << xrange_min << ":" << xrange_max << "]\n";
        gp << "set yrange [" << yrange_min << ":" << yrange_max << "]\n";
    };

    static void renderCollect(Gnuplot &gp, FunctionGraphRefs &graphs, LabelRefs &labels)
    {
        gp << "plot ";
        for (auto labelIt = labels.begin(); labelIt < labels.end() - 1;
             labelIt++)
        {
            gp << "'-' " << labelIt->get() << ", ";
        }
        gp << "'-' " << labels.back().get() << "\n";
        for (const auto &graph : graphs)
        {
            gp.send1d(graph.get());
        }
    }

    template <class... Args>
    static void renderCollect(Gnuplot &gp, FunctionGraphRefs &graphs, LabelRefs &labels, const FunctionGraph &graph, const std::string &label, const Args &... args)
    {
        graphs.emplace_back(graph);
        labels.emplace_back(label);
        Plot::renderCollect(gp, graphs, labels, args...);
    }

private:
    FunctionGraphs graphs;
    Labels labels;
};
}
}

#endif  // CPPSTAT_PLOT_H
