be-ef
======
A small [brainfuck][1] interpreter written as a C++ refresher for myself. 
[CMake][2] must be installed in order to build.

About brainfuck
----------------
Brainfuck is a super minimalist language with only 8 commands. In brainfuck,
there is an infinitely long tape with cells on it. Each cell is initialized to
zero at the beginning of any brainfuck program. Then there is a pointer called
the data pointer that initially points to the zeroth cell of the tape, which
can be moved both to the left and the right(of course, moving to the left of
the zeroth cell is not allowed). The commands are(the current cell is the one
to which the data pointer is pointing):

<style>
.center{
    text-align: center;
}
td{
    padding-left: 50px;
    padding-right: 50px;
}
</style>

<table>
    <tr>
        <th>Command</th>
        <th>What it does</th>
    </tr>
    <tr>
        <td class="center"><code>&gt;</code></td>
        <td>Increment the data pointer/Move the data pointer to the
        next cell to the right of the current cell.</td>
    </tr>
    <tr>
        <td class="center"><code>&lt;</code></td>
        <td>Decrement the data pointer/Move the data pointer to the next
        cell to the left of the current cell</td>
    </tr>
    <tr>
        <td class="center"><code>+</code></td>
        <td>Increment the value in the current cell.</td>
    </tr>
    <tr>
        <td class="center"><code>-</code></td>
        <td>Decrement the value in the current cell.</td>
    </tr>
    <tr>
        <td class="center"><code>.</code></td>
        <td>Output the data byte under the pointer(in the current cell) as
        an ASCII encoded character.</td>
    </tr>
    <tr>
        <td class="center"><code>,</code></td>
        <td>Accept one byte of input and store it under the pointer.</td>
    </tr>
    <tr>
        <td class="center"><code>[</code></td>
        <td>If the byte at the data pointer is zero, jump to the command
        following the matching `]` command. Note that the data pointer is
        not altered, the instruction pointer is.</td>
    </tr>
    <tr>
        <td class="center"><code>]</code></td>
        <td>If the byte under the data pointer is non-zero, continue
        executing the next command, else jump back to the matching `[`
        command in the code. This command also has no effect on the data
        pointer, but changes the instruction pointer.</td>
    </tr>
</table>


Usage
------


    $ git clone https://github.com/yati-sagade/be-ef.git
    $ cd be-ef
    $ mkdir build && cd build
    $ cmake ..
    $ make
    $ ./bf ../99bottles.bf

[1]:http://en.wikipedia.org/wiki/Brainfuck
[2]:http://www.cmake.org/cmake/help/install.html
