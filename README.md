# project-2-dsm-and-map-reduce-framework-Aman-ai
project-2-dsm-and-map-reduce-framework-Aman-ai created by GitHub Classroom


1. Distributed Mutex Lock
    The distributed mutex lock is used for mutual exclusion across a distributed system (that is across different nodes)

2. Distributed Shared Memory
    Different nodes in the system share memory through invalidation based protocol. 
    
3. For testing purposes (Part 1):
        a. Go to /seq-consistency directory.
        b. run make clean
        c. run make 
        d. refer the node_list.txt to check the ip addresses of the participating nodes (Last node is the directory node)
        e. run ./dir_node on directory server (Last in node_list.txt)
        f. run ./p1 <Total Nodes Participating (Including Directory Node) OR Length of node_list.txt file>
        g. run ./p2 <Total Nodes Participating (Including Directory Node) OR Length of node_list.txt file>
        h. run ./p3 <Total Nodes Participating (Including Directory Node) OR Length of node_list.txt file>
       
4. For testing purposes (Part 2):
         a. Go to /dist_sorting folder
         b. run make clean
         c. run make 
         d. refer the node_list.txt to check the ip addresses of the participating nodes (Last node is the directory node)
         e. run ./dir_node on directory server (Last in node_list.txt)
         f. run ./app1 <process_num> <Total_process>

5. For testing Purposes (Part 3):
   This is for testing the distributed mutex lock
   a. Go to /test_mutex directory
   b. run make clean
   c. run make 
   d. refer the node_list.txt to check the ip addresses of the participating nodes (Last node is the directory node)
   e. run ./dir_node on directory server (Last in node_list.txt)
   f. run ./dist_mem_mtx_impl <Total Nodes Participating (Including Directory Node) OR Length of node_list.txt file>
