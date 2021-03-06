(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   GreedySearch.ml                                    :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/31 10:27:02 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/05 10:51:16 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH)
            (EventHandler : GenericInterfaces.EVENT_HANDLER
			 with type state = Graph.t) ->
  struct

	type graph = Graph.t

    type parent = None | Some of graph * graph_info
	 and graph_info = { parent      : parent;
						h           : int; }

	type opened_container = graph Stack.t
	type info_container = (graph, graph_info) Hashtbl.t


	let retreive_steps graph info =
	  let rec aux info acc =
		match info.parent with
		| Some (graph, info)        -> aux info (graph::acc)
		| _                         -> acc
	  in
	  aux info [graph]

	let solve grasrc gragoal he =

	  let infosrc = { parent		= None;
					  h				= he grasrc; } in

	  let opened = Stack.create () in
	  Stack.push grasrc opened;
	  let infos = Hashtbl.create 300 in
	  Hashtbl.add infos grasrc infosrc;

	  (* Loop *)
	  let rec aux rep =

		let gra = Stack.pop opened in
		let info = Hashtbl.find infos gra in

		let rep = EventHandler.tick_report
					rep info.h (Stack.length opened + 1)
					(Hashtbl.length infos) in

		if Graph.equal gra gragoal then (

		  EventHandler.finalize_report rep (retreive_steps gra info)

		)
		else (

		  let rec build_succ l acc =
			match l with
			| hd::tl when not (Hashtbl.mem infos hd)
			  -> let info' = { parent	= Some (gra, info);
							   h		= he hd; } in
				 build_succ tl ((hd, info')::acc)
			| _::tl
			  -> build_succ tl acc
			| _
			  -> acc
		  in
		  let built_succ = List.sort (fun (_, {h = a}) (_, {h = b}) -> b - a)
									 (build_succ (Graph.successors gra) []) in
		  let rec push_succ = function
			| (gra', info')::tl		-> Stack.push gra' opened;
									   Hashtbl.add infos gra' info';
									   push_succ tl
			| _						-> ()
		  in
		  push_succ built_succ;
		  aux rep

		)
	  in (* End of Loop *)
	  let rep = aux (EventHandler.new_report infosrc.h) in
	  EventHandler.pushq (EventHandler.Progress 1.);
	  EventHandler.pushq (EventHandler.Success rep);
	  ()

  end
