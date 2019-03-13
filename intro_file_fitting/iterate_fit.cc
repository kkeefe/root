// currently pulled from project where i needed it to return a slope, now I want it to return a set of points to graph for differences.. 

vector<double_t> iterate_fit(TGraph *tg, double_t x_min, double_t x_max, int num_fits)
{

    TF1 *my_func = new TF1("my_func", "pol2");
    my_func->SetParNames("s0", "s1", "s2");

    vector<double_t> slopes;
    double_t width = (x_max - x_min) / num_fits;
    //previous parameters to guess for fits (avoid explosive fits)
    double_t prev_p0, prev_p1, prev_p2;    
    //printf("avg_slope\tmid_slope\tthresh_mid\n");
    for (int i = 0; i < num_fits; ++i)
    {
        double_t value = x_min + (width * (i + 1 / 2)); //take the derivative in the middle of the current range..
        double_t low_slope, high_slope;

        my_func->SetParameter("p0", prev_p0);
        my_func->SetParameter("p1", prev_p1);
        my_func->SetParameter("p2", prev_p2);

        tg->Fit(my_func, "QW", "L", x_min + (width * i), x_min + (width * (i + 1)));
        residual_fits(tg,my_func,x_min + (width * i),x_min + (width * (i + 1)));
        
        if (my_func->IsZombie()) {
            prev_p0 = my_func->GetParameter("p0");
            prev_p1 = my_func->GetParameter("p1");
            prev_p2 = my_func->GetParameter("p2");
        }
        //derivative stuff..       
        slopes.push_back(my_func->Derivative(value));

        // low_slope = my_func->Derivative(x_min + (width * i));
        // high_slope = my_func->Derivative(x_min + (width * (i + 1)));

        // cout << (low_slope + high_slope) / 2 << "\t" << my_func->Derivative(value) << "\t" << value << endl;

        //my_func->Print();
        //cout << my_func->GetParameter("s0") << "\t" << my_func->GetParameter("s1") << "\t" << my_func->GetParameter("s2") << "\t\t" << width << endl;
        //cout << "current derivative: " << slopes[i] << endl;
    }
    return slopes;
}