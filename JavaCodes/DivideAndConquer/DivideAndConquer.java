package algoDs;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.Scanner;
/* 
 Java code to apply Prim's on weighted directed graph to find Minimum Spanning Tree & 
 Bellman-Ford algorithm on weighted undirected graph to single-source shortest path
*/
public class Donga124735Mamidala124768 {
  public static void main(String[] args) {
    int dgVertices = 5, undgVertices = 5;/* Number of vertices in both directed(dg) & undirect(undg) garph */
    /* creating objects for both graphs */
    DirectedGraph dGraph = new DirectedGraph(dgVertices);
    UndirectedGraph undGraph = new UndirectedGraph(undgVertices);

    // Adding edges to the directed graph starting from 0
    dGraph.addWeightedEdge(0, 1, 2);
    dGraph.addWeightedEdge(0, 3, 6);
    dGraph.addWeightedEdge(1, 2, 3);
    dGraph.addWeightedEdge(1, 3, 8);
    dGraph.addWeightedEdge(1, 4, 5);
    dGraph.addWeightedEdge(2, 4, 7);
    dGraph.addWeightedEdge(3, 4, 9);

    // Adding edges to the undirected graph starting from 0
    undGraph.addWeightedEdge(0, 1, 4);
    undGraph.addWeightedEdge(0, 2, 1);
    undGraph.addWeightedEdge(1, 2, 2);
    undGraph.addWeightedEdge(1, 3, 5);
    undGraph.addWeightedEdge(2, 3, 2);
    undGraph.addWeightedEdge(2, 4, 1);
    undGraph.addWeightedEdge(3, 4, 3);
    
    Scanner scanner = new Scanner(System.in);
    int choice;
    do {
      System.out.println("Choose an option:");
      System.out.println("1. Finding Single-Source Shortest Path (SSSP) using Bellman-Ford algorithm");
      System.out.println("2. Finding Minimum Spanning Tree (MST) using Prim's algorithm");
      System.out.println("3. Exit of tasks");
      System.out.print("Enter your choice(1,2 and 3): ");
      choice = scanner.nextInt();

      switch (choice) {
        case 1:
          int ssspSrc = 0;
          dGraph.getSSSP(ssspSrc); // finding single-src shortest path using Bellman-Ford algorithm and min heap
          break;
        case 2:
          undGraph.getMST(); // finding minimum spanning tree using Prim's algorithm and min heap
          break;
        case 3:
          System.out.println("Exiting...");
          break;
        default:
          System.out.println("Invalid choice. Please try again.");
      }
    } while (choice != 3);

    scanner.close();

    int ssspSrc = 0;
    dGraph.getSSSP(ssspSrc); // finding single-src shortest path using Bellman-Ford algorithm and min heap
    // Note for SSSP: if there is edge from point a to b then the default value (MAX_INT) is printed as distance 
    undGraph.getMST(); // finding minimum spanning tree using Prim's algorithm and min heap
  }
}

/* class DirectedGraph to create a directed graph & get SSSP */
class DirectedGraph {
  private int vertices;
  private List<GraphEdge>[] adjList;

  DirectedGraph(int vertices) {
    this.vertices = vertices;
    adjList = new ArrayList[vertices];
    for (int ele = 0; ele < vertices; ++ele) {
      adjList[ele] = new ArrayList<>();
    }
  }
  /* GraphEdge class to add edges to graph */
  class GraphEdge {
    int src, dest, W; // sourceVertex, destinationVertex & cost between the src & dest
    GraphEdge(int src, int dest, int W) {
      this.dest = dest;
      this.W = W;
      this.src = src;
    }
  }

  /* SSSPNode class to store a vertex with its cost */
  class SSSPNode {
    int vertex, cost;
    SSSPNode(int vertex, int cost) {
      this.cost = cost;
      this.vertex = vertex;
    }
  }

  /* Adding a new edge to the graph */
  void addWeightedEdge(int src, int dest, int W) {
    GraphEdge newEdge = new GraphEdge(src, dest, W);
    adjList[src].add(newEdge);
  }

  /* Print the shortest distances from the src */
  void printGraph(int[] cost) {
    System.out.println("SSSP:");
    System.out.println("Vertex \t  Cost from src");
    for (int k = 0; k < vertices; ++k) {
      System.out.println("(" + k + ")" + "--------->" + cost[k]);
    }
  }

  /* Get Single-Source Shortest Path for a given source in a directed graph */
  void getSSSP(int src) {
    int[] cost = new int[vertices];
    /* assigning infinite value for all the keys */
    Arrays.fill(cost, Integer.MAX_VALUE);
    /* beginning with src */
    cost[src] = 0;

    /* Creating a min heap */
    PriorityQueue<SSSPNode> minHeap = new PriorityQueue<>(
      vertices,
      Comparator.comparingInt(node -> node.cost)
    );
    minHeap.offer(new SSSPNode(src, cost[src]));
    /* while minHeap is not empty, get min cost from src to all other vertices */
    while (!minHeap.isEmpty()) {
      int x = minHeap.poll().vertex;
      for (GraphEdge e : adjList[x]) {
        int y = e.dest;
        int z = e.W;
        if (cost[x] + z < cost[y] && cost[x] != Integer.MAX_VALUE) {
          cost[y] = z + cost[x];
          minHeap.offer(new SSSPNode(y, cost[y]));
        }
      }
    }
    printGraph(cost);
  }
}

/* Class UndirectedGraph to create an undirected graph & get MST */
class UndirectedGraph {
  private int vertices;
  private List<GraphEdge>[] adjList;

  UndirectedGraph(int vertices) {
    this.vertices = vertices;
    adjList = new ArrayList[this.vertices];
    for (int v = 0; v < vertices; ++v) {
      adjList[v] = new ArrayList<>();
    }
  }

  /* GraphEdge class to add edges to graph */
  class GraphEdge {
    int src, dest, W; // sourceVertex, destinationVertex & cost between the src & dest
    GraphEdge(int src, int dest, int W) {
      this.W = W;
      this.src = src;
      this.dest = dest;
    }
  }


  /* MSTNode class to store vertex & its elements value */
  class MSTNode {
    int vertex, ele;
    MSTNode(int vertex, int ele) {
      this.ele = ele;
      this.vertex = vertex;
    }
  }

  /* Inserting an new edge to the undirected graph */
  void addWeightedEdge(int src, int dest, int W) {
    GraphEdge newEdge = new GraphEdge(src, dest, W);
    adjList[src].add(newEdge);
    GraphEdge newRevEdge = new GraphEdge(dest, src, W); // adding a new reverse edge
    adjList[dest].add(newRevEdge);
  }

  /* Print the final MST */
  void printGraph(int[] sourceV, int src, int[] ele) {
    System.out.println("MST:");
    System.out.println("SEdge DEdge\t  Weight");
    for (int destV = 0; destV < vertices; destV++) {
      if (destV == src) {
        continue;
      }
        System.out.println(
          "(" +
          sourceV[destV] +
          " --- " +
          destV +
          ")" +
          "----------->" +
          ele[destV]
        );
      }
    }
    /* creates a file with name dotFile.dot and writes data of best edges to travel in the graph */
    void printDotFile(int[] sourceV, int src, int[] ele) throws IOException{
      FileWriter file = new FileWriter("dotFile.dot");
      file.write("graph MinimumSpanningTree{\n");
      file.write("edge [ color = \"red\"]\n");
      int edgecost =0;
      for (int destV = 0; destV < vertices; destV++) {
        if (destV == src) {
          continue;
        }
        edgecost+=ele[destV];
        file.write( sourceV[destV] + " -- " + destV + "[label = \""+ele[destV] + "\"]\n");
        }
        file.write("}");
        file.close();
        System.out.println("                                ");
        System.out.println("Total weights cost: " + edgecost);
        System.out.println("Check dotFile for Graphviz Code in the project file " );
        System.out.println("                                ");
    }

  /* get Minimum Spanning Tree for a given undirected graph */
  void getMST() {
    int src = 0;
    int[] ele = new int[vertices];
    int[] sourceV = new int[vertices];
    boolean[] finalArr = new boolean[vertices];
    /* assigning infinite value for all the keys */
    Arrays.fill(ele, Integer.MAX_VALUE);

    /* Creating a min heap */
    PriorityQueue<MSTNode> minHeap = new PriorityQueue<>(
      vertices,
      Comparator.comparingInt(node -> node.ele)
    );

    /* Beginning from the src vertex */
    ele[src] = 0;
    minHeap.offer(new MSTNode(src, ele[src]));

    /* while minHeap is not empty, get min cost from src to all other vertices */
    while (!minHeap.isEmpty()) {
      /* getting the vertex with min cost */
      int x = minHeap.poll().vertex;
      finalArr[x] = true;

      /* traversing through all the outgoing edges from x */
      for (GraphEdge e : adjList[x]) {
        int y = e.dest;
        int w = e.W;
        /* checking the weight of x & y is < current value of y && dest is not in min spanning tree &  */
        if (w < ele[y] && !finalArr[y]) {
          ele[y] = w;
          sourceV[y] = x;
          minHeap.offer(new MSTNode(y, ele[y]));
        }
      }
    }
    printGraph(sourceV, src, ele);
    try {
      printDotFile(sourceV, src, ele);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
