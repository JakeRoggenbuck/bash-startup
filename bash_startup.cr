class Aliases
	@aliases : Array(Array(String))
	@lines : Array(String)

	def initialize
		@lines = [] of String
		@aliases = [] of Array(String)
		get_lines()
		get_aliases()
	end

	def get_lines
		(File.read_lines(Path["~/.bashrc"].expand(home: true))).each() do |line|
			@lines << line.lstrip
		end
	end

	def get_aliases
		line_num = 0
		(@lines).each() do |line|
			_alias = [] of String
			if line.includes?("alias ")
				unless line[0] == '#'

					_alias << line

					last_line = @lines[line_num - 1]
					if last_line.starts_with?('#')
						_alias << last_line
					end

					@aliases << _alias
				end
			end
			line_num += 1
		end
	end

	def get_random_alias
		rand = Random.new
		random_index = rand.rand(0..@aliases.size-1)
		return @aliases[random_index]
	end

	def make_look_nice
		_alias = get_random_alias()
		before = "\n\t"
		message = before + _alias[1] + before + _alias[0] + "\n\n"
		puts message
	end
end

aliases = Aliases.new
aliases.make_look_nice()
