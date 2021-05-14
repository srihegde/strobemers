#include <iostream>
#include <fstream>
#include <unordered_map>
#include "robin_hood.h"
#include <vector>
#include <string>
#include <chrono>  // for high_resolution_clock

#include "index.hpp"




typedef robin_hood::unordered_map< std::string , std::string > queries;
typedef robin_hood::unordered_map< unsigned int , std::string > references;
typedef robin_hood::unordered_map< unsigned int, std::string > idx_to_acc;

typedef robin_hood::unordered_map< uint64_t, std::tuple<uint64_t, unsigned int >> vector_index;

typedef std::vector< std::tuple<uint64_t, unsigned int, unsigned int, unsigned int, unsigned int>> mers_vector;



static void read_references(references &seqs, idx_to_acc &acc_map, std::string fn)
{
    std::ifstream file(fn);
    std::string line, seq;
    int ref_index = 0;
    while (getline(file, line)) {
        if (line[0] == '>') {
//            std::cout << ref_index << " " << line << std::endl;
            if (seq.length() > 0){
                seqs[ref_index -1] = seq;
//                std::cout << ref_index - 1 << " here " << seq << " " << seq.length() << " " << seq.size() << std::endl;
//                generate_kmers(h, k, seq, ref_index);
            }
            acc_map[ref_index] = line;
            ref_index++;
            seq = "";
        }
        else {
            seq += line;
        }
    }
    if (seq.length() > 0){
        seqs[ref_index -1] = seq;
//        std::cout << ref_index -1 << " here2 " << seq << std::endl;
//        generate_kmers(h, k, seq, ref_index);
    }
    file.close();
}

//static void print_diagnostics_new(mers_vector_order1  kmers, idx_to_acc &acc_map) {
//    uint64_t tot_index_size = 0;
//    for (int i = 0; i < kmers.size(); ++i)
//    {
//        // access using []
//        auto t = kmers[i];
////        std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
//        tot_index_size += sizeof(t);
////        std::cout << sizeof(t) << std::endl;
//    }
//    std::cout << "Total size of index vector : " << tot_index_size/1000000  << " Mb." << std::endl;
//
//}

//static void print_diagnostics_new2(mers_vector_order1 &mers_vector, vector_index &mers_index ) {
//    uint64_t tot_flat_vector_size = 0;
//    for (int i = 0; i < mers_vector.size(); ++i)
//    {
//        // access using []
//        auto t = mers_vector[i];
////        std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << "), ";
//        tot_flat_vector_size += sizeof(t);
//    }
//    std::cout << "Total size of flat kmer vector : " << tot_flat_vector_size/1000000  << " Mb." << std::endl;
//
//    uint64_t tot_hashtable_index_size = 0;
//    for (auto &it : mers_index)
//    {
////        std::cout << it.first << ": (" << std::get<0>(it.second) << ", " << std::get<1>(it.second) << "), " ;
//        tot_hashtable_index_size += sizeof(it.first);
//        tot_hashtable_index_size += sizeof(it.second);
//    }
//    std::cout << "Total size of hash table index : " << tot_hashtable_index_size/1000000  << " Mb." << std::endl;
//}

//static void print_diagnostics_new3(mers_vector_order2 &mers_vector, vector_index &mers_index ) {
//    uint64_t tot_flat_vector_size = 0;
//    for (int i = 0; i < mers_vector.size(); ++i)
//    {
//        // access using []
//        auto t = mers_vector[i];
////        std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << "), ";
//        tot_flat_vector_size += sizeof(t);
//    }
//    std::cout << "Total size of flat kmer vector : " << tot_flat_vector_size/1000000  << " Mb." << std::endl;
//
//    uint64_t tot_hashtable_index_size = 0;
//    for (auto &it : mers_index)
//    {
////        std::cout << it.first << ": (" << std::get<0>(it.second) << ", " << std::get<1>(it.second) << "), " ;
//        tot_hashtable_index_size += sizeof(it.first);
//        tot_hashtable_index_size += sizeof(it.second);
//    }
//    std::cout << "Total size of hash table index : " << tot_hashtable_index_size/1000000  << " Mb." << std::endl;
//}

//static void print_diagnostics(seq_index1 &h, idx_to_acc &acc_map) {
//    uint64_t tot_index_size = 0;
//    for (auto &it : h)
//    {
////        std::cout << "\nKey: " << it.first << ",  values: ";
//        tot_index_size += sizeof(it.first);
//        for (auto &t : it.second) // it.second is the vector, i is a tuple
//        {
////            std::cout << "tuple: " << std::get<0>(t) << " " << std::get<1>(t)  << std::endl;
//            tot_index_size += sizeof(t);
//        }
////        std::cout << "Size of key : " << sizeof(it.first)  << " byte" << "Size of vector : " << sizeof(it.second)  << " byte" << std::endl;
//        tot_index_size += sizeof(it.second);
//
//    }
//
////    // Traversing an unordered map
////    for (auto x : acc_map)
////        std::cout << x.first << " " << x.second << std::endl;
//
//    std::cout << "Total size of index : " << tot_index_size/1000000  << " Mb." << std::endl;
//
//}


//static void print_diagnostics2(seq_index2 &h, idx_to_acc &acc_map) {
//    uint64_t tot_index_size = 0;
//
//    for (auto &it : h)
//    {
////        std::cout << "\nKey: " << it.first << ",  values: ";
//        tot_index_size += sizeof(it.first);
//        for (auto &t : it.second) // it.second is the vector, i is a tuple
//        {
////            std::cout << "(" << std::get<0>(t) << " " << std::get<1>(t)  << " " << std::get<2>(t) << ") ";
//            tot_index_size += sizeof(t);
//        }
////        std::cout << ". Size of key : " << sizeof(it.first)  << " byte" << "Size of vector : " << sizeof(it.second)  << " byte" << std::endl;
//        tot_index_size += sizeof(it.second);
//
//    }
//
////    // Traversing an unordered map
////    for (auto x : acc_map) {
////        std::cout << x.first << " " << x.second << std::endl;
////    }
//
//    std::cout << "Total size of index : " << tot_index_size/1000000  << " Mb." << std::endl;
//
//}


static void print_diagnostics_new4(mers_vector &mers_vector, vector_index mers_index ) {
    uint64_t tot_flat_vector_size = 0;
    for (size_t i = 0; i < mers_vector.size(); ++i)
    {
        // access using []
        auto t = mers_vector[i];
//        std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << ", " << std::get<4>(t) << "), ";
        tot_flat_vector_size += sizeof(t);
    }
    std::cout << "Total size of flat mers-vector : " << tot_flat_vector_size/1000000  << " Mb." << std::endl;

//    uint64_t tot_hashtable_index_size = 0;
//    for (auto &it : mers_index)
//    {
////        std::cout << it.first << ": (" << std::get<0>(it.second) << ", " << std::get<1>(it.second) << "), " ;
//        tot_hashtable_index_size += sizeof(it.first);
//        tot_hashtable_index_size += sizeof(it.second);
//    }
//    std::cout << "Total size of hash table index : " << tot_hashtable_index_size/1000000  << " Mb." << std::endl;

    std::cout << "Total size of hash table index : " << (mers_index.size() * sizeof(vector_index::value_type))/1000000 << " Mb." << "\n";
}


std::vector<nam> find_nams(mers_vector &query_mers, mers_vector &mers_vector, vector_index &mers_index, int k){
    std::cout << "ENTER FIND NAMS " <<  std::endl;
    robin_hood::unordered_map< unsigned int, std::vector<hit>> hits_per_ref; // [ref_id] -> vector( struct hit)

    for (size_t i = 0; i < query_mers.size(); ++i)
    {
        // access using []
        auto q = query_mers[i];
        uint64_t mer_hashv = std::get<0>(q);
        if (mers_index.find(mer_hashv) != mers_index.end()){ //  In  index
            std::tuple<uint64_t, unsigned int> mer;
            mer = mers_index[mer_hashv];
            uint64_t offset = std::get<0>(mer);
            unsigned int count = std::get<1>(mer);
            for(size_t i = offset; i < offset+count; ++i)
            {
                hit h;
                h.query_s = std::get<2>(q);
                h.query_e = std::get<4>(q) + k;

                auto r = mers_vector[i];
                h.ref_s = std::get<2>(r);
                h.ref_e = std::get<4>(r) + k;


                unsigned int ref_id = std::get<1>(r);
                hits_per_ref[ref_id].push_back(h);
//                std::cout << "Hit! " << h.query_s << ", " << h.query_e << ", " << h.ref_s << ", " << h.ref_e << ", " << std::endl;

            }
        }
    }

    // TODO: Make set an unordered_set to speedup lookup, insertion and deletion to O(1) instead of O(log n)
    std::vector<nam>  open_nams;
    robin_hood::unordered_map<unsigned int, std::vector<nam>> final_nams; // [ref_id] -> vector(struct nam)

    for (auto &it : hits_per_ref)
    {
        unsigned int ref_id = it.first;
        std::vector<hit> hits = it.second;
        open_nams = std::vector<nam> (); // Initialize vector
        for (size_t i = 0; i < hits.size(); ++i){
            hit h = hits[i];
            bool is_added = false;

            for (auto & o : open_nams) {
//            for (size_t i = 0; i < open_nams.size(); ++i){
//                nam o = open_nams[i];

                // Extend NAM
                if ( ( o.query_s <= h.query_s) && (h.query_s <= o.query_e ) && ( o.ref_s <= h.ref_s) && (h.ref_s <= o.ref_e) ){
                    if (h.query_e > o.query_e){
//                        std::cout << "Changing query " << o.query_e <<  " to " << h.query_e << std::endl;
                        o.query_e = h.query_e;
//                        std::cout << o.query_e << std::endl;
                    }
                    if (h.ref_e > o.ref_e){
//                        std::cout << "Changing ref " << o.ref_e <<  " to " << h.ref_e << std::endl;
                        o.ref_e = h.ref_e;
                    }
                    is_added = true;
                }
            }

            // Output all NAMs from open_matches to final_nams that the current hit have passed
            for (size_t i = 0; i < open_nams.size(); ++i){
                nam n = open_nams[i];
                if (n.query_e < h.query_s) {
                    final_nams[ref_id].push_back(open_nams[i]);
                }
            }

            // Remove all NAMs from open_matches that the current hit have passed
            unsigned int c = h.query_s;
            auto predicate = [c](decltype(open_nams)::value_type const& nam) {return nam.query_e < c;};
            open_nams.erase(std::remove_if(open_nams.begin(), open_nams.end(), predicate), open_nams.end());

            // Add the hit to open matches
            if (not is_added){
                nam n;
                n.query_s = h.query_s;
                n.query_e = h.query_e;
                n.ref_s = h.ref_s;
                n.ref_e = h.ref_e;
                n.ref_id = ref_id;
                open_nams.push_back(n);
            }

        }

        // Add all current open_matches to final NAMs
        for (size_t i = 0; i < open_nams.size(); ++i){
            final_nams[ref_id].push_back(open_nams[i]);
        }
    }

    for (auto &it : final_nams){
        for (auto &n : it.second) // it.second is the vector, i is a tuple
        {
            std::cout << it.first << ": (" << n.query_s << ", " << n.query_e << ", " << n.ref_s << ", " << n.ref_e << ")" << std::endl;
        }
    }

    std::vector<nam> all_nams_flattened;
    // flatten out to final_nams vector

    return all_nams_flattened;
}

int main (int argc, char *argv[])
{

    ///////////////////// INPUT /////////////////////////

    std::string filename  = "example2.txt";
    std::string reads_filename  = "example2_reads.txt";
//    std::string filename  = "ecoli.fa";
//    std::string filename  = "chr21.fa";
    std::string choice = "kmers";
//    std::string choice = "minstrobes";
//   std::string choice = "hybridstrobes";
//   std::string choice = "randstrobes";
    int n = 3;
    int k = 10;
    int w_min = 11;
    int w_max = 30;
    assert(k <= w_min && "k have to be smaller than w_min");
    std::string* file_p;
    file_p = &filename;
    references ref_seqs;
    idx_to_acc acc_map;
    read_references(ref_seqs, acc_map, filename);

    //////////////////////////////////////////////////////


    //////////// CREATE INDEX OF REF SEQUENCES /////////////////

    // Record index creation start time
    auto start = std::chrono::high_resolution_clock::now();

    three_pos_index tmp_index; // hash table holding all reference mers

    if (choice == "kmers" ){
        for (auto x : ref_seqs){
            mers_vector kmers; //  kmer hash value, pos, chr_id
            kmers = seq_to_kmers(k, x.second, x.first);
            tmp_index[x.first] = kmers;
        }
    }
    else if (choice == "hybridstrobes" ){
        if (n == 2 ){
            for (auto x : ref_seqs){
                mers_vector hybridstrobes2; // pos, chr_id, kmer hash value
                hybridstrobes2 = seq_to_hybridstrobes2(n, k, w_min, w_max, x.second, x.first);
                tmp_index[x.first] = hybridstrobes2;
            }
        }
//        else if (n == 3){ for (auto x : ref_seqs){generate_hybridstrobe3_index(h, k, x.second, x.first);}}
    }
    else if (choice == "minstrobes" ){
        if (n == 2 ){
            for (auto x : ref_seqs){
//                generate_minstrobe2_index(h, n, k, w_min, w_max, x.second, x.first);
                mers_vector minstrobes2; // pos, chr_id, kmer hash value
                minstrobes2 = seq_to_minstrobes2(n, k, w_min, w_max, x.second, x.first);
                tmp_index[x.first] = minstrobes2;
            }
        }
//        else if (n == 3){ for (auto x : ref_seqs){generate_minstrobe3_index(h, k, x.second, x.first);}}
    }
    else if (choice == "randstrobes" ){
        if (n == 2 ){
            for (auto x : ref_seqs){
                mers_vector randstrobes2; // pos, chr_id, kmer hash value
                randstrobes2 = seq_to_randstrobes2(n, k, w_min, w_max, x.second, x.first);
                tmp_index[x.first] = randstrobes2;
            }
        }
        else if (n == 3){
            for (auto x : ref_seqs){
                mers_vector randstrobes3; // pos, chr_id, kmer hash value
                randstrobes3 = seq_to_randstrobes3(n, k, w_min, w_max, x.second, x.first);
                tmp_index[x.first] = randstrobes3;
            }
        }
    }
    else {
        std::cout << choice << "not implemented : " << std::endl;
    }


    mers_vector all_mers_vector;
    all_mers_vector = construct_flat_vector_three_pos(tmp_index);
    robin_hood::unordered_map< uint64_t, std::tuple<uint64_t, unsigned int >> mers_index; // k-mer -> (offset in flat_vector, occurence count )
    mers_index = index_vector_three_pos(all_mers_vector); // construct index over flat array
    tmp_index.clear();
    print_diagnostics_new4(all_mers_vector, mers_index);

    //////////////////////////////////////////////////////////////////////////

    // Record index creation end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Total time generating index: " << elapsed.count() << " s\n" <<  std::endl;



    ///////////////////////////// MAP ///////////////////////////////////////

    // Record matching time
    auto start_map = std::chrono::high_resolution_clock::now();

    std::ifstream query_file(reads_filename);
    std::ofstream output_file;
    output_file.open ("output.tsv");

    std::string line, seq, prev_acc;
    unsigned int q_id = 0;
    mers_vector query_mers; // pos, chr_id, kmer hash value
    while (getline(query_file, line)) {
        if (line[0] == '>') {
            if (seq.length() > 0){
                // generate mers here
                if (choice == "kmers" ){
                    query_mers = seq_to_kmers(k, seq, q_id);
                }
                else if (choice == "randstrobes" ){
                    if (n == 2 ){
                        query_mers = seq_to_randstrobes2(n, k, w_min, w_max, seq, q_id);
                        }

                    else if (n == 3){
                        query_mers = seq_to_randstrobes3(n, k, w_min, w_max, seq, q_id);
                    }
                }
//                std::cout << "HERE " << line << std::endl;
                // Find NAMs
                std::cout << "Processing read, kmers generated: " << query_mers.size() << ", read length: " <<  seq.length() << line << std::endl;
                std::vector<nam> nams; // (r_id, r_pos_start, r_pos_end, q_pos_start, q_pos_end)
                nams = find_nams(query_mers, all_mers_vector, mers_index, k);
                std::cout <<  "NAMs generated: " << nams.size() << line << std::endl;

                // Output results
//              output_file << "> " <<  prev_acc << "\n";
//              output_file << "  " << ref_acc << " " << ref_p << " " << q_pos << " " << "\n";
//              outfile.write("  {0} {1} {2} {3}\n".format(ref_acc, ref_p, q_pos, k))

            }
            prev_acc = line.substr(1, line.length() -1);
            seq = "";
            q_id ++;
        }
        else {
            seq += line;
        }
    }
    if (seq.length() > 0){
        if (choice == "kmers" ){
            mers_vector kmers; // pos, chr_id, kmer hash value
            kmers = seq_to_kmers(k, seq, q_id);
        }
    }

    query_file.close();
    output_file.close();


    // Record mapping end time
    auto finish_map = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_map = finish_map - start_map;
    std::cout << "Total time generating matches: " << elapsed_map.count() << " s\n" <<  std::endl;


    //////////////////////////////////////////////////////////////////////////


    /////////////////////// FIND AND OUTPUT NAMs ///////////////////////////////





}

